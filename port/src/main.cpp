// Application entry point: locate the disc image, bring up aurora, then hand
// control to the game's original main() (renamed to game_main for the PC build).

#include <aurora/aurora.h>
#include <aurora/dvd.h>
#include <aurora/main.h>

#include "port/os.h"

#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_messagebox.h>

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

extern "C" void game_main(void);
extern "C" void port_data_fixups(void);
extern "C" void port_user_ini_load(const char* userPath);
extern "C" void port_begin_first_frame(void);
#ifdef __EMSCRIPTEN__
extern "C" bool port_web_open_disc(void);
extern "C" void port_web_report_fatal(const char* message);
#endif

extern "C" void port_touch_init(void);

static void log_callback(AuroraLogLevel level, const char* module, const char* message, unsigned int len)
{
    static const char* names[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
    FILE* out = level >= LOG_ERROR ? stderr : stdout;
    fprintf(out, "[%s: %s] %.*s\n", names[level], module, (int)len, message);
    if (level == LOG_FATAL)
    {
        fflush(out);
#ifdef __EMSCRIPTEN__
        port_web_report_fatal(std::string(message, len).c_str());
#endif
        abort();
    }
}

static bool is_disc_image(const fs::path& p)
{
    std::error_code ec;
    if (!fs::is_regular_file(p, ec))
        return false;
    auto ext = p.extension().string();
    for (auto& c : ext)
        c = (char)tolower(c);
    return ext == ".iso" || ext == ".gcm" || ext == ".rvz" || ext == ".ciso" || ext == ".gcz" || ext == ".wia";
}

static std::string first_disc_in(const fs::path& dir)
{
    std::error_code ec;
    if (!fs::is_directory(dir, ec))
        return {};
    for (const auto& entry : fs::directory_iterator(dir, ec))
    {
        if (is_disc_image(entry.path()))
            return entry.path().string();
    }
    return {};
}

// Disc image: a path argument, $MSSB_ISO, mario_baseball.iso next to the
// repo (or a parent of it), or the first image in the user folder or next to the executable.
static std::string find_disc(int argc, char** argv, const char* userPath)
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-' && is_disc_image(argv[i]))
            return argv[i];
    }
    if (const char* env = getenv("MSSB_ISO"); env && is_disc_image(env))
        return env;
#ifdef MSSB_REPO_DIR
    // ../mario_baseball.iso next to the checkout (worktrees live deeper).
    for (fs::path dir = fs::path(MSSB_REPO_DIR); dir.has_parent_path() && dir != dir.parent_path();
         dir = dir.parent_path())
    {
        if (fs::path p = dir.parent_path() / "mario_baseball.iso"; is_disc_image(p))
            return p.string();
    }
#endif

    std::vector<fs::path> dirs;
    if (userPath)
        dirs.emplace_back(userPath);
    if (const char* base = SDL_GetBasePath())
    {
        fs::path p(base);
        dirs.push_back(p);
        for (int i = 0; i < 4 && p.has_parent_path(); i++)
        {
            p = p.parent_path();
            dirs.push_back(p);
        }
    }
    for (const auto& dir : dirs)
    {
        if (auto found = first_disc_in(dir); !found.empty())
            return found;
    }
    return {};
}

int aurora_main(int argc, char** argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    AuroraConfig config{};
    config.appName = "Mario Superstar Baseball";
    config.logCallback = &log_callback;
    config.logLevel = LOG_INFO;
    config.vsync = true;
    config.windowWidth = 1280;
    config.windowHeight = 960;
    config.mem1Size = MEM1_DEFAULT_SIZE;
    config.mem2Size = ARAM_DEFAULT_SIZE;
    config.allowTextureDumps = getenv("MSSB_DUMP_TEXTURES") != nullptr;
#ifdef __EMSCRIPTEN__
    // IndexedDB-backed, mounted by the page. Online play starts from a fresh
    // memory card instead, so each player's saves and options can't make the
    // two games differ.
    config.userPath = port_net_active() ? "/tmp/netplay" : "/mssb";
    config.cachePath = "/tmp";
#else
    // MSSB_USER_DIR: a separate user data folder (memory card, user.ini,
    // bindings), e.g. for tests that must not touch the real saves.
    if (const char* dir = getenv("MSSB_USER_DIR"); dir && dir[0])
        config.userPath = dir;
#endif
    // The phone's accelerometer isn't a controller (it would hide the touch controls).
    SDL_SetHint("SDL_ACCELEROMETER_AS_JOYSTICK", "0");
    AuroraInfo info = aurora_initialize(argc, argv, &config);
    port_crash_init(info.userPath);
    port_touch_init();
    port_user_ini_load(info.userPath);

#ifdef __EMSCRIPTEN__
    if (!port_web_open_disc())
    {
        port_web_report_fatal("Couldn't read the disc image. It needs to be Mario Superstar Baseball (USA): "
                              ".iso, .gcm or .ciso.");
        return 1;
    }
#else
    std::string disc = find_disc(argc, argv, info.userPath);
    if (disc.empty() || !aurora_dvd_open(disc.c_str()))
    {
        std::string msg = "Couldn't find a Mario Superstar Baseball (USA) disc image.\n\n"
                          "Set MSSB_ISO, pass its path as an argument, or put the .iso in:\n";
        msg += info.userPath ? info.userPath : "(user data folder)";
        fprintf(stderr, "%s\n", msg.c_str());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Mario Superstar Baseball", msg.c_str(), info.window);
        aurora_shutdown();
        return 1;
    }
    fprintf(stderr, "[port] disc: %s\n", disc.c_str());
#endif

    port_os_init();
    port_pad_init_defaults();
    port_begin_first_frame();
    port_data_fixups();
    game_main();
    port_audio_shutdown();
    aurora_shutdown();
    return 0;
}
