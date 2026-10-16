import struct
B=open('build/port/bankdump/bank_06.bin','rb').read()
be32=lambda o:struct.unpack_from('>I',B,o)[0]; be16=lambda o:struct.unpack_from('>H',B,o)[0]
TOFF=be32(0)
def entry(i):
    e=TOFF+4+i*0x20
    return dict(d=TOFF+be32(e), t=TOFF+be32(e+4), h=be16(e+8), w=be16(e+10), fmt=B[e+0x17])
def indices(i):
    en=entry(i); w,h=en['w'],en['h']; p=en['d']
    W=(w+7)//8*8; H=(h+7)//8*8
    g=[[0]*W for _ in range(H)]
    for by in range(0,H,8):
        for bx in range(0,W,8):
            for y in range(8):
                for x in range(8):
                    byte=B[p+(y*8+x)//2]; v=(byte>>4) if x%2==0 else byte&15
                    g[by+y][bx+x]=v
            p+=32
    return g,w,h
PAL=[be16(entry(49)['t']+2*k) for k in range(16)]
ALPHA=[v>>8 for v in PAL]; INT=[v&255 for v in PAL]
