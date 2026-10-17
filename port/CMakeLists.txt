cmake_minimum_required(VERSION 3.25)

# PC build of Mario Superstar Baseball on aurora. See port/README.md.
#   cmake -S port -B build/port -G Ninja && ninja -C build/port

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif ()

if (APPLE AND NOT CMAKE_OSX_SYSROOT AND NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
    execute_process(COMMAND xcrun --sdk macosx --show-sdk-path
            OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()

project(mssb LANGUAGES C CXX VERSION 0.1.0)
if (APPLE)
    enable_language(OBJC OBJCXX)
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(MSSB_ROOT ${CMAKE_SOURCE_DIR}/.. ABSOLUTE)
set(AURORA_DIR ${CMAKE_SOURCE_DIR}/extern/aurora)

# aurora is the bigmah/aurora mssb-port branch: strikers' revision
# (strikers-port + its Emscripten/WebGPU commit 3fbe54a) plus MSSB's GX/card
# fixes. Change aurora there and bump the submodule.

# Compiling the game only needs aurora's headers; the full aurora build
# (Dawn, SDL3, nod) is needed to link the executable (Phase 2).
option(MSSB_AURORA "Configure aurora (needed to link the mssb executable)" ON)
if (EMSCRIPTEN)
    # Browser build (port/tools/build_web.sh, as strikers'): single-threaded,
    # WebGPU via emdawnwebgpu, SDL3 built from source, and a minimal GCM
    # reader in place of nod (port/web/nod).
    set(AURORA_SDL3_PROVIDER vendor CACHE STRING "" FORCE)
    set(AURORA_SDL3_LINKAGE static CACHE STRING "" FORCE)
    set(AURORA_CACHE_USE_ZSTD OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF)
    add_library(mssb_web_ZLIB INTERFACE)
    target_compile_options(mssb_web_ZLIB INTERFACE -sUSE_ZLIB=1)
    target_link_options(mssb_web_ZLIB INTERFACE -sUSE_ZLIB=1)
    add_library(mssb_web_PNG INTERFACE)
    target_compile_options(mssb_web_PNG INTERFACE -sUSE_LIBPNG=1)
    target_link_options(mssb_web_PNG INTERFACE -sUSE_LIBPNG=1)
    add_library(ZLIB::ZLIB ALIAS mssb_web_ZLIB)
    add_library(PNG::PNG ALIAS mssb_web_PNG)
    add_library(nod_web STATIC ${CMAKE_SOURCE_DIR}/web/nod/nod_gcm.cpp)
    target_include_directories(nod_web PUBLIC ${CMAKE_SOURCE_DIR}/web/nod/include)
    add_library(nod::nod ALIAS nod_web)
endif ()
if (IOS)
    # nod is a Rust library with no iOS package: use the web build's minimal reader
    # for plain .iso/.gcm images instead (aurora reads the disc through a stream).
    add_library(nod_ios STATIC ${CMAKE_SOURCE_DIR}/web/nod/nod_gcm.cpp)
    target_include_directories(nod_ios PUBLIC ${CMAKE_SOURCE_DIR}/web/nod/include)
    add_library(nod::nod ALIAS nod_ios)
endif ()
if (MSSB_AURORA)
    set(AURORA_ENABLE_DVD ON CACHE BOOL "" FORCE)
    set(AURORA_ENABLE_CARD ON CACHE BOOL "" FORCE)
    add_subdirectory(${AURORA_DIR} aurora EXCLUDE_FROM_ALL)
endif ()

include(${CMAKE_SOURCE_DIR}/sources.cmake)

# Include order matters on case-insensitive filesystems: aurora's
# <dolphin/...> must win over the decomp's include/Dolphin/... for the SDK.
# The decomp's own SDK headers forward to aurora's under TARGET_PC.
set(MSSB_INCLUDES
    $<$<BOOL:${EMSCRIPTEN}>:${CMAKE_SOURCE_DIR}/web/include>
    ${CMAKE_SOURCE_DIR}/include_game
    ${CMAKE_SOURCE_DIR}/include
    ${AURORA_DIR}/include
    ${MSSB_ROOT}/include
)

set(MSSB_DEFS TARGET_PC NONMATCHING=1 VERSION=0 VERNUM=0 NDEBUG=1)

set(MSSB_COMMON_FLAGS
    -fno-strict-aliasing
    -fwrapv
    -fno-delete-null-pointer-checks
    -fsigned-char
    -ffp-contract=off
    -fno-strict-return
    -fno-finite-loops
    -fno-common
    -ferror-limit=0
    # Game sources declare memcpy/memset themselves: no fortify macros.
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0
)
if (EMSCRIPTEN)
    # Online play needs both browsers to compute the same game. Decompiled code
    # sometimes reads a local before setting it, and stack garbage differs with
    # what ran before (audio, interrupts): start every local at zero.
    list(APPEND MSSB_COMMON_FLAGS -ftrivial-auto-var-init=zero)
endif ()

# 64-bit problems: pointers must not be stored in 32-bit integers, and calls
# need prototypes (an implicit int return truncates pointers). Everything
# else stays quiet: the decomp is full of harmless MWCC-isms.
option(MSSB_WERROR_64 "Make the 64-bit pointer/int warnings errors" ON)
set(MSSB_64_WARNINGS
    shorten-64-to-32
    int-to-pointer-cast
    pointer-to-int-cast
    incompatible-function-pointer-types
    implicit-function-declaration
    int-conversion
)
set(MSSB_PORT_WARNINGS -Wno-everything)
foreach (w ${MSSB_64_WARNINGS})
    list(APPEND MSSB_PORT_WARNINGS -W${w})
    if (MSSB_WERROR_64)
        list(APPEND MSSB_PORT_WARNINGS -Werror=${w})
    endif ()
endforeach ()

# Debug: report calls through function pointers of another type than the
# callee's (they trap in wasm). Needs a clang with UBSan's function check
# (Homebrew LLVM: -DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang).
option(MSSB_SANITIZE_FUNCTION "Build game code with -fsanitize=function" OFF)
if (MSSB_SANITIZE_FUNCTION)
    list(APPEND MSSB_PORT_WARNINGS -fsanitize=function -fsanitize-recover=function)
    # Our own handler (port/tools/fncheck) logs every (site, callee) pair.
endif ()

# wasm-ld has no section bounds, but it lays data out in input order: on the
# web build each module's sources are bracketed by generated marker objects
# so port/src/modules.c can reset the module's .data/.bss at each load
# (port/include/port/module_sections.h).
function(mssb_bracket_modules list_var kind)
    if (NOT EMSCRIPTEN)
        return()
    endif ()
    set(in ${${list_var}})
    set(out)
    set(rest ${in})
    foreach (module challenge menus game)
        if (kind STREQUAL "src")
            set(regex "/src/${module}/")
        else ()
            set(regex "/gen/${module}(/|_data\\.c$)")
        endif ()
        set(mod ${rest})
        list(FILTER mod INCLUDE REGEX "${regex}")
        list(FILTER rest EXCLUDE REGEX "${regex}")
        if (mod)
            foreach (edge begin end)
                set(f ${CMAKE_BINARY_DIR}/modmark/${module}_${kind}_${edge}.c)
                file(WRITE ${f}.tmp "// Generated: ${module} ${kind} data/bss ${edge} marker (port/CMakeLists.txt).\n"
                    "char mssb_${module}_${kind}_d_${edge} = 1;\nchar mssb_${module}_${kind}_b_${edge};\n")
                file(COPY_FILE ${f}.tmp ${f} ONLY_IF_DIFFERENT)
            endforeach ()
            list(APPEND out ${CMAKE_BINARY_DIR}/modmark/${module}_${kind}_begin.c ${mod}
                ${CMAKE_BINARY_DIR}/modmark/${module}_${kind}_end.c)
        endif ()
    endforeach ()
    set(${list_var} ${rest} ${out} PARENT_SCOPE)
endfunction ()

# Game code from main.dol, game.rel, menus.rel and challenge.rel.
# PC-only code that needs the game's headers (compiled like the game).
file(GLOB MSSB_PORT_GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/game/*.c)
list(APPEND MSSB_GAME_SOURCES ${MSSB_PORT_GAME_SOURCES})
mssb_bracket_modules(MSSB_GAME_SOURCES src)
# Xcode (iOS) can't take object libraries with repeated file names (src/*/rep_00B0.c):
# its object files get hashed names. There they're static libraries, linked whole.
if (IOS)
    set(MSSB_OBJLIB STATIC)
else ()
    set(MSSB_OBJLIB OBJECT)
endif ()
add_library(mssb_game ${MSSB_OBJLIB} ${MSSB_GAME_SOURCES})
target_include_directories(mssb_game PRIVATE ${MSSB_INCLUDES})
target_compile_definitions(mssb_game PRIVATE ${MSSB_DEFS})
target_compile_options(mssb_game PRIVATE ${MSSB_COMMON_FLAGS} ${MSSB_PORT_WARNINGS}
    -include ${CMAKE_SOURCE_DIR}/include/port/prelude.h)

# --- MusyX (audio) ---
# The MusyX 2.0.3 runtime from strikers (port/musyx, ported to PC there; MIT,
# from the musyx decomp), with strikers' DSP/AI emulation in port/src/audio.
# It is compiled against its own headers (port/musyx/include); the game uses
# include/musyx, whose API must stay ABI-compatible with it (see the
# TARGET_PC notes in include/musyx/musyx.h).
# The runtime hands the DSP emulation 32-bit "physical" addresses by
# truncating pointers on purpose (game-heap offsets: the heap is 4GB-aligned,
# port/include/port/game_heap.h), so the 64-bit cast warnings stay off here.
add_library(musyx STATIC
    ${CMAKE_SOURCE_DIR}/musyx/src/CheapReverb/creverb_fx.c
    ${CMAKE_SOURCE_DIR}/musyx/src/CheapReverb/creverb.c
    ${CMAKE_SOURCE_DIR}/musyx/src/Chorus/chorus_fx.c
    ${CMAKE_SOURCE_DIR}/musyx/src/Delay/delay_fx.c
    ${CMAKE_SOURCE_DIR}/musyx/src/dsp_import.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hardware.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hw_aramdma.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hw_dolphin.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hw_dspctrl.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hw_memory.c
    ${CMAKE_SOURCE_DIR}/musyx/src/hw_volconv.c
    ${CMAKE_SOURCE_DIR}/musyx/src/s_data.c
    ${CMAKE_SOURCE_DIR}/musyx/src/seq_api.c
    ${CMAKE_SOURCE_DIR}/musyx/src/seq.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd_init.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd_math.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd_midictrl.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd_service.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd_synthapi.c
    ${CMAKE_SOURCE_DIR}/musyx/src/snd3d.c
    ${CMAKE_SOURCE_DIR}/musyx/src/StdReverb/reverb_fx.c
    ${CMAKE_SOURCE_DIR}/musyx/src/StdReverb/reverb.c
    ${CMAKE_SOURCE_DIR}/musyx/src/stream.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synth_ac.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synth_adsr.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synth_dbtab.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synth_vsamples.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synth.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synthdata.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synthmacros.c
    ${CMAKE_SOURCE_DIR}/musyx/src/synthvoice.c
)
target_include_directories(musyx PRIVATE ${CMAKE_SOURCE_DIR}/musyx/include ${AURORA_DIR}/include)
target_compile_definitions(musyx PRIVATE TARGET_PC NDEBUG=1 MUSY_TARGET=MUSY_TARGET_DOLPHIN
    MUSY_VERSION_MAJOR=2 MUSY_VERSION_MINOR=0 MUSY_VERSION_PATCH=3)
target_compile_options(musyx PRIVATE ${MSSB_COMMON_FLAGS} -Wno-everything
    -Werror=implicit-function-declaration -Werror=int-conversion)
# DSP microcode HLE and AI output (from strikers). "port/..." headers come in
# through -iquote: port/include also shadows <math.h> for the game.
file(GLOB MSSB_AUDIO_SOURCES CONFIGURE_DEPENDS src/audio/*.c src/audio/*.cpp)
add_library(mssb_audio STATIC ${MSSB_AUDIO_SOURCES})
target_include_directories(mssb_audio PRIVATE ${CMAKE_SOURCE_DIR}/musyx/include ${AURORA_DIR}/include)
target_compile_options(mssb_audio PRIVATE -iquote ${CMAKE_SOURCE_DIR}/include
    ${MSSB_COMMON_FLAGS} -Wno-everything)
target_compile_definitions(mssb_audio PRIVATE TARGET_PC NDEBUG=1 MUSY_TARGET=MUSY_TARGET_DOLPHIN
    MUSY_VERSION_MAJOR=2 MUSY_VERSION_MINOR=0 MUSY_VERSION_PATCH=3)
if (MSSB_AURORA)
    target_link_libraries(musyx PRIVATE aurora::core)
    target_link_libraries(mssb_audio PRIVATE aurora::core)
endif ()

# ---- Generated data (port/gen, from port/tools/gen_data.py) ----
# Definitions of the data objects no game source defines yet, generated from
# orig/ with the C types the game sources declare. Same flags as the game,
# minus the 64-bit errors: initializers take addresses of functions declared
# without prototypes.
include(${CMAKE_SOURCE_DIR}/gen/sources.cmake)
mssb_bracket_modules(MSSB_GEN_SOURCES gen)
add_library(mssb_gen ${MSSB_OBJLIB} ${MSSB_GEN_SOURCES})
target_include_directories(mssb_gen PRIVATE ${MSSB_INCLUDES})
target_compile_definitions(mssb_gen PRIVATE ${MSSB_DEFS})
target_compile_options(mssb_gen PRIVATE ${MSSB_COMMON_FLAGS} -Wno-everything
    -include ${CMAKE_SOURCE_DIR}/include/port/prelude.h)
# ---- end generated data ----

# The game's main() becomes game_main(); port/src/main.cpp owns the entry point.
set_source_files_properties(${MSSB_ROOT}/src/main/file_80008E00.c PROPERTIES COMPILE_DEFINITIONS main=game_main)

# REL modules are linked in: give each module's _prolog/_epilog/_unresolved a
# unique name (port/src/modules.c calls them).
# PORT_MODULE_ID (the REL's module id) puts each module's data and bss into
# sections of their own, reset at every load like a freshly linked REL
# (port/include/port/module_sections.h, port/src/modules.c).
set(MSSB_MODULE_ID_challenge 1)
set(MSSB_MODULE_ID_menus 2)
set(MSSB_MODULE_ID_game 3)
foreach (module menus game challenge)
    set(module_sources ${MSSB_GAME_SOURCES})
    list(FILTER module_sources INCLUDE REGEX "/src/${module}/")
    set_property(SOURCE ${module_sources} APPEND PROPERTY COMPILE_DEFINITIONS
        _prolog=${module}_prolog _epilog=${module}_epilog _unresolved=${module}_unresolved
        PORT_MODULE_ID=${MSSB_MODULE_ID_${module}})
    set(module_gen ${MSSB_GEN_SOURCES})
    list(FILTER module_gen INCLUDE REGEX "/gen/${module}(/|_data\\.c$)")
    set_property(SOURCE ${module_gen} APPEND PROPERTY COMPILE_DEFINITIONS
        PORT_MODULE_ID=${MSSB_MODULE_ID_${module}})
endforeach ()

# PC-only code (port/src) and the executable.
file(GLOB_RECURSE PORT_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)
list(FILTER PORT_SOURCES EXCLUDE REGEX "/src/audio/")
if (EMSCRIPTEN)
    # wasm32 pointers are already 32-bit: no reserved heap region, no
    # signal-based crash handler. The game's threads are fibers (os.cpp
    # includes port/web/src/os_threads_web.inc).
    list(FILTER PORT_SOURCES EXCLUDE REGEX "/src/(crash|game_heap)\\.cpp$|/src/game_heap_dlmalloc\\.c$")
    file(GLOB WEB_SOURCES CONFIGURE_DEPENDS web/src/*.cpp)
    list(APPEND PORT_SOURCES ${WEB_SOURCES})
endif ()
if (IOS)
    add_executable(mssb ${PORT_SOURCES})
    add_dependencies(mssb mssb_game mssb_gen)
    target_link_options(mssb PRIVATE "LINKER:-force_load,$<TARGET_FILE:mssb_game>"
        "LINKER:-force_load,$<TARGET_FILE:mssb_gen>")
else ()
    add_executable(mssb ${PORT_SOURCES} $<TARGET_OBJECTS:mssb_game> $<TARGET_OBJECTS:mssb_gen>)
endif ()
# port/src sees aurora and port/include, not the game's shadow headers.
target_include_directories(mssb PRIVATE $<$<BOOL:${EMSCRIPTEN}>:${CMAKE_SOURCE_DIR}/web/include> ${CMAKE_SOURCE_DIR}/include ${AURORA_DIR}/include)
target_compile_definitions(mssb PRIVATE ${MSSB_DEFS} MSSB_REPO_DIR="${MSSB_ROOT}")
target_compile_options(mssb PRIVATE ${MSSB_COMMON_FLAGS} -Wno-everything)
if (MSSB_AURORA)
    if (MSSB_SANITIZE_FUNCTION)
        target_sources(mssb PRIVATE ${CMAKE_SOURCE_DIR}/tools/fncheck/ubsan_fn.c)
    endif ()
    target_link_libraries(mssb PRIVATE musyx mssb_audio aurora::core aurora::gx aurora::vi aurora::pad
        aurora::si aurora::dvd aurora::card aurora::mtx aurora::os aurora::main)
endif ()

if (IOS)
    # iPhone app (port/tools/make_ios.sh): an Xcode project with the disc image and
    # the pipeline cache in the bundle, signed with your team (automatic signing).
    set(MSSB_IOS_TEAM "" CACHE STRING "Apple developer team ID (signing)")
    set(MSSB_IOS_BUNDLE_ID "com.doublea819.mssb" CACHE STRING "iOS bundle identifier")
    set(MSSB_IOS_DISC "${MSSB_ROOT}/../Mario Superstar Baseball (USA).iso" CACHE FILEPATH
        "Disc image copied into the app")
    set(MSSB_IOS_RESOURCES ${CMAKE_SOURCE_DIR}/ios/Assets.xcassets)
    if (EXISTS "${MSSB_IOS_DISC}")
        list(APPEND MSSB_IOS_RESOURCES "${MSSB_IOS_DISC}")
    else ()
        message(WARNING "MSSB_IOS_DISC not found (${MSSB_IOS_DISC}): the app will have no disc")
    endif ()
    if (EXISTS "${MSSB_ROOT}/build/port/initial_pipeline_cache.db")
        list(APPEND MSSB_IOS_RESOURCES "${MSSB_ROOT}/build/port/initial_pipeline_cache.db")
    endif ()
    target_sources(mssb PRIVATE ${MSSB_IOS_RESOURCES})
    set_target_properties(mssb PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/ios/Info.plist.in
        MACOSX_BUNDLE_GUI_IDENTIFIER ${MSSB_IOS_BUNDLE_ID}
        MACOSX_BUNDLE_BUNDLE_VERSION 1
        RESOURCE "${MSSB_IOS_RESOURCES}"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${MSSB_IOS_BUNDLE_ID}
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${MSSB_IOS_TEAM}"
        XCODE_ATTRIBUTE_CODE_SIGN_STYLE Automatic
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS ${CMAKE_SOURCE_DIR}/ios/mssb.entitlements
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 17.0
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon
        XCODE_ATTRIBUTE_ENABLE_BITCODE NO
        XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf
        XCODE_GENERATE_SCHEME TRUE)
endif ()

if (EMSCRIPTEN)
    option(MSSB_WEB_FPCAST "Emulate function pointer casts (slow; debugging only)" OFF)
    set(MSSB_WEB_LINK_OPT "-O3" CACHE STRING "Link optimisation level for the web build")
    # The game's OS threads are Emscripten fibers, which need Asyncify (JSPI
    # can't switch fibers); disc reads that miss the page's cache and frame
    # pacing also suspend through it.
    # wasm traps on indirect calls whose signature differs from the callee's;
    # the sources are fixed for that (port/README.md), so no fpcast emulation.
    target_link_options(mssb PRIVATE
        -sASYNCIFY
        $<$<BOOL:${MSSB_WEB_FPCAST}>:-sEMULATE_FUNCTION_POINTER_CASTS=1>
        ${MSSB_WEB_LINK_OPT}
        -sASYNCIFY_STACK_SIZE=1MB
        -sALLOW_MEMORY_GROWTH=1
        -sINITIAL_MEMORY=512MB
        -sMAXIMUM_MEMORY=3GB
        -sSTACK_SIZE=8MB
        -sENVIRONMENT=web
        -sEXIT_RUNTIME=0
        -sINVOKE_RUN=0
        -sMODULARIZE=0
        -sEXPORTED_RUNTIME_METHODS=['callMain','FS','IDBFS','HEAPU8','addRunDependency','removeRunDependency','ENV']
        -sEXPORTED_FUNCTIONS=['_main','_malloc','_free']
        -lidbfs.js
        --profiling-funcs)
    set_target_properties(mssb PROPERTIES OUTPUT_NAME "mssb" SUFFIX ".js")
    # Copy the page and its scripts next to the build output.
    add_custom_target(mssb_page ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/web/index.html ${CMAKE_SOURCE_DIR}/web/loader.js ${CMAKE_SOURCE_DIR}/web/net.js
            ${CMAKE_SOURCE_DIR}/web/pad.js ${CMAKE_SOURCE_DIR}/web/touch.js
            ${CMAKE_SOURCE_DIR}/web/initial_pipeline_cache.bin.gz ${CMAKE_SOURCE_DIR}/web/boot_blocks.json
            $<TARGET_FILE_DIR:mssb>)
endif ()
