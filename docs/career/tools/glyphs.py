import math
from PIL import Image, ImageDraw
exec(open('docs/career/tools/seg3.py').read().split("img=Image.new")[0])
def glyph_table():
    G={}  # letter -> list of (labelidx, ua, ub)
    for i,word in LAB.items():
        cuts,prof,g,w,h=cuts_for(i)
        parts=word.split(' ')
        for (a,cs,b),pw in zip(cuts,parts):
            bounds=[a]+cs+[b+1]
            for k,ch in enumerate(pw):
                G.setdefault(ch,[]).append((i,bounds[k],bounds[k+1]))
    return G
def strip_pixels(i,ua,ub,pad=2):
    g,w,h=indices(i); y0=h//2
    out={}
    for y in range(h):
        for x in range(w):
            u=x+SLOPE*(y-y0)+20
            if ua-pad<=u<ub+pad:
                out[(x,y)]=(g[y][x], u)
    return out
if __name__=='__main__':
    G=glyph_table()
    print(sorted(G.keys()), {k:len(v) for k,v in G.items()})
    img=Image.new('RGB',(1200,600),(30,60,120)); d=ImageDraw.Draw(img)
    X=0;Y=0
    for ch in sorted(G):
        for (i,ua,ub) in G[ch]:
            px=strip_pixels(i,ua,ub,0)
            xs=[p[0] for p in px]; 
            mn=min(xs)
            for (x,y),(v,u) in px.items():
                a=ALPHA[v]; I=INT[v]
                c=(int(I*a/255+30*(1-a/255)),)*3
                d.rectangle([X+(x-mn)*3,Y+y*3,X+(x-mn)*3+2,Y+y*3+2],fill=c)
            d.text((X,Y+66),ch+str(i),fill=(255,255,0))
            X+=(max(xs)-mn)*3+12
            if X>1100: X=0; Y+=85
    img.save('glyphs.png')
