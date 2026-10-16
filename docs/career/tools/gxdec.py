import struct, sys
from PIL import Image
def be32(b,o): return struct.unpack_from('>I',b,o)[0]
def be16(b,o): return struct.unpack_from('>H',b,o)[0]
def rgb5a3(v):
    if v & 0x8000:
        r=(v>>10)&31; g=(v>>5)&31; b=v&31
        return (r*255//31,g*255//31,b*255//31,255)
    a=(v>>12)&7; r=(v>>8)&15; g=(v>>4)&15; b=v&15
    return (r*17,g*17,b*17,a*255//7)
def rgb565(v):
    return ((v>>11)*255//31, ((v>>5)&63)*255//63, (v&31)*255//31, 255)
def ia8(v): i=v&0xff; a=v>>8; return (i,i,i,a)
def pal_color(fmt, v):
    return [ia8, rgb565, rgb5a3][fmt](v)
BLK={0:(8,8,4),1:(8,4,8),2:(8,4,8),3:(4,4,16),4:(4,4,16),5:(4,4,16),6:(4,4,32),8:(8,8,4),9:(8,4,8),10:(4,4,16),14:(8,8,4)}
def decode(b, off, w, h, fmt, tlut=None, tfmt=0, tn=0):
    img=Image.new('RGBA',(w,h))
    px=img.load()
    if fmt==14:  # CMPR
        p=off
        for by in range(0,h,8):
            for bx in range(0,w,8):
                for sb in range(4):
                    sx=bx+(sb%2)*4; sy=by+(sb//2)*4
                    c0=be16(b,p); c1=be16(b,p+2); bits=be32(b,p+4); p+=8
                    a=rgb565(c0); c=rgb565(c1)
                    if c0>c1:
                        cols=[a,c,tuple((2*a[i]+c[i])//3 for i in range(3))+(255,),tuple((a[i]+2*c[i])//3 for i in range(3))+(255,)]
                    else:
                        cols=[a,c,tuple((a[i]+c[i])//2 for i in range(3))+(255,),(0,0,0,0)]
                    for yy in range(4):
                        for xx in range(4):
                            idx=(bits>>(30-2*(yy*4+xx)))&3
                            if sx+xx<w and sy+yy<h: px[sx+xx,sy+yy]=cols[idx]
        return img
    bw,bh,bpp=BLK[fmt]
    p=off
    pal=None
    if fmt in (8,9,10):
        pal=[pal_color(tfmt, be16(b,tlut+2*i)) for i in range(tn)]
    for by in range(0,h,bh):
        for bx in range(0,w,bw):
            if fmt==6:
                ar=b[p:p+32]; gb=b[p+32:p+64]; p+=64
                for i in range(16):
                    x=bx+i%4; y=by+i//4
                    if x<w and y<h: px[x,y]=(ar[2*i+1],gb[2*i],gb[2*i+1],ar[2*i])
                continue
            for y in range(bh):
                for x in range(bw):
                    X=bx+x; Y=by+y
                    if bpp==4:
                        byte=b[p+(y*bw+x)//2]; v=(byte>>4) if x%2==0 else byte&15
                    elif bpp==8: v=b[p+y*bw+x]
                    else: v=be16(b,p+2*(y*bw+x))
                    if X<w and Y<h:
                        if fmt==0: px[X,Y]=(v*17,)*3+(255,)
                        elif fmt==1: px[X,Y]=(v,)*3+(255,)
                        elif fmt==2: i=v&15; a=v>>4; px[X,Y]=(i*17,)*3+(a*17,)
                        elif fmt==3: px[X,Y]=ia8(v)
                        elif fmt==4: px[X,Y]=rgb565(v)
                        elif fmt==5: px[X,Y]=rgb5a3(v)
                        elif fmt in (8,9,10): px[X,Y]=pal[v] if v<len(pal) else (255,0,255,255)
            p+=bw*bh*bpp//8
    return img
def bank(path, outdir, prefix):
    b=open(path,'rb').read()
    toff=be32(b,0); aoff=be32(b,4)
    cnt=be16(b,toff)
    res=[]
    for i in range(cnt):
        e=toff+4+i*0x20
        d=be32(b,e); t=be32(b,e+4); h=be16(b,e+8); w=be16(b,e+10); fmt=b[e+0x17]; tn=be16(b,e+0x18); tf=b[e+0x1A]
        try:
            img=decode(b,toff+d,w,h,fmt,toff+t if t else None,tf,tn)
            img.save(f"{outdir}/{prefix}_{i:03d}_{w}x{h}_f{fmt}.png")
            res.append((i,w,h,fmt))
        except Exception as ex:
            print('fail',i,w,h,fmt,ex)
    return res
if __name__=='__main__':
    r=bank(sys.argv[1],sys.argv[2],sys.argv[3])
    for x in r: print(x)
