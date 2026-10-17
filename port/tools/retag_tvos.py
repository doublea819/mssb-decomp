#!/usr/bin/env python3
# Retags iOS arm64 Mach-O objects (in .a archives or .o files) as tvOS, in place:
# LC_BUILD_VERSION platform IOS -> TVOS (and LC_VERSION_MIN_IPHONEOS -> _TVOS).
# Used for Dawn, which has a prebuilt iOS package but none for tvOS (same Metal API).
#   retag_tvos.py <file.a|file.o> ...
import struct, sys

LC_BUILD_VERSION = 0x32
LC_VERSION_MIN_IPHONEOS = 0x25
LC_VERSION_MIN_TVOS = 0x2F
PLATFORM_IOS, PLATFORM_TVOS = 2, 3
MINOS = (17 << 16)  # tvOS 17.0

def retag_macho(buf, off):
    magic = struct.unpack_from('<I', buf, off)[0]
    if magic != 0xFEEDFACF:
        return 0
    ncmds = struct.unpack_from('<I', buf, off + 16)[0]
    p = off + 32
    n = 0
    for _ in range(ncmds):
        cmd, size = struct.unpack_from('<II', buf, p)
        if cmd == LC_BUILD_VERSION:
            plat = struct.unpack_from('<I', buf, p + 8)[0]
            if plat in (PLATFORM_IOS, PLATFORM_TVOS):
                struct.pack_into('<II', buf, p + 8, PLATFORM_TVOS, MINOS)
                n += 1
        elif cmd == LC_VERSION_MIN_IPHONEOS:
            struct.pack_into('<I', buf, p, LC_VERSION_MIN_TVOS)
            struct.pack_into('<I', buf, p + 8, MINOS)
            n += 1
        p += size
    return n

def retag_archive(buf):
    if buf[:8] != b'!<arch>\n':
        return retag_macho(buf, 0)
    p, n = 8, 0
    while p + 60 <= len(buf):
        hdr = buf[p:p + 60]
        name = hdr[:16].decode('ascii', 'replace').strip()
        size = int(hdr[48:58].decode().strip())
        data = p + 60
        extra = 0
        if name.startswith('#1/'):  # BSD long name stored before the data
            extra = int(name[3:])
        n += retag_macho(buf, data + extra) if size - extra >= 32 else 0
        p = data + size + (size & 1)
    return n

for path in sys.argv[1:]:
    with open(path, 'rb') as f:
        buf = bytearray(f.read())
    n = retag_archive(buf)
    with open(path, 'wb') as f:
        f.write(buf)
    print(f'{path}: {n} objects retagged for tvOS')
