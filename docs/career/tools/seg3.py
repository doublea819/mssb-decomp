import math
from PIL import Image, ImageDraw
exec(open('docs/career/tools/lab.py').read())
LAB={49:"Exhibition Game",52:"Challenge",53:"Toy Field",54:"Minigames",55:"Practice",56:"Records",57:"Options"}
SLOPE=0.36
def core_prof(i):
    g,w,h=indices(i); y0=h//2
    prof=[0.0]*(w+40)
    for y in range(h):
        for x in range(w):
            a=ALPHA[g[y][x]]; I=INT[g[y][x]]
            if a>200 and I>200:
                prof[int(math.floor(x+SLOPE*(y-y0)))+20]+=1
    return prof,g,w,h
def cuts_for(i):
    word=LAB[i]
    prof,g,w,h=core_prof(i)
    nz=[u for u,v in enumerate(prof) if v>0]
    lo,hi=nz[0],nz[-1]
    parts=word.split(' ')
    # split words by largest zero gaps
    gaps=[]
    u=lo
    while u<hi:
        if prof[u]==0:
            s=u
            while prof[u]==0: u+=1
            gaps.append((u-s,s,u))
        u+=1
    gaps.sort(reverse=True)
    wordgaps=sorted(gaps[:len(parts)-1],key=lambda t:t[1])
    spans=[];start=lo
    for _,s,e in wordgaps: spans.append((start,s-1)); start=e
    spans.append((start,hi))
    allcuts=[]
    for (a,b),pw in zip(spans,parts):
        n=len(pw)
        # candidate minima
        cands=[]
        for u in range(a+3,b-2):
            cands.append((prof[u],u))
        chosen=[]
        for k in range(1,n):
            exp=a+(b-a)*k/n
            best=min((c for c in cands if abs(c[1]-exp)<=5 and all(abs(c[1]-x)>=4 for x in chosen)),key=lambda c:(c[0],abs(c[1]-exp)))
            chosen.append(best[1])
        allcuts.append((a,sorted(chosen),b))
    return allcuts,prof,g,w,h
img=Image.new('RGB',(160*5,24*5*7+40),(30,60,120)); d=ImageDraw.Draw(img)
for row,i in enumerate(LAB):
    cuts,prof,g,w,h=cuts_for(i)
    y0=h//2
    for y in range(h):
        for x in range(w):
            a=ALPHA[g[y][x]]; I=INT[g[y][x]]
            c=(int(I*a/255+30*(1-a/255)),)*3
            d.rectangle([x*5,row*120+y*5,x*5+4,row*120+y*5+4],fill=c)
    for a,cs,b in cuts:
        for u in [a]+cs+[b+1]:
            # line x = u-20 - SLOPE*(y-y0)
            pts=[((u-20-SLOPE*(y-y0))*5,row*120+y*5) for y in (0,h)]
            d.line(pts,fill=(255,0,0),width=1)
    print(LAB[i],cuts)
img.save('cuts.png')
