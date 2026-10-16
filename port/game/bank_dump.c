// Saves each menu sprite bank (textures + animations, as loaded from the disc, before the PC
// byte swaps) once to build/port/bankdump/bank_XX.bin. Used to build the Career menu's button
// words from the game's own button pictures (tools: docs/career/).
#include "mssbTypes.h"

#include <stdio.h>
#include <sys/stat.h>

void port_bank_dump(s32 id, const void* data, u32 size) {
    static u8 s_done[256];
    char path[256];
    FILE* f;
    if (id < 0 || id > 255 || s_done[id] || data == NULL || size == 0 || size > (32u << 20)) {
        return;
    }
    s_done[id] = 1;
    mkdir("build", 0755);
    mkdir("build/port", 0755);
    mkdir("build/port/bankdump", 0755);
    snprintf(path, sizeof(path), "build/port/bankdump/bank_%02x.bin", (unsigned)id);
    f = fopen(path, "wb");
    if (f == NULL) {
        return;
    }
    fwrite(data, 1, size, f);
    fclose(f);
    fprintf(stderr, "[bankdump] bank %#x: %u bytes -> %s\n", (unsigned)id, (unsigned)size, path);
}
