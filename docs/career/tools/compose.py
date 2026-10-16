import math
from PIL import Image, ImageDraw
exec(open('docs/career/tools/glyphs.py').read().split("if __name__")[0])
PICK={'P':55,'l':53,'a':55,'y':53,'G':49,'m':54,'e':53,'T':53,'r':56,'i':53,'n':57,'g':52,'o':56,'s':56,
      't':57,'C':52,'c':55,'h':52,'F':53,'d':53,'E':49,'p':57,'R':56,'O':57,'M':54}
G=glyph_table()
OVERRIDE={'m':(54,115,136)}
def pick(ch):
    if ch in OVERRIDE: return OVERRIDE[ch]
    for (i,ua,ub) in G[ch]:
        if i==PICK[ch]: return (i,ua,ub)
    return G[ch][0]
SPACE=9
def compose(word):
    W,H=160,24
    out=[[14]*W for _ in range(H)]
    alpha=[[0]*W for _ in range(H)]
    # layout in u-space
    items=[];U=0
    for ch in word:
        if ch==' ': U+=SPACE; continue
        i,ua,ub=pick(ch); items.append((ch,i,ua,ub,U)); U+=ub-ua
    total=U
    start=98-total/2
    for ch,i,ua,ub,Uk in items:
        dx=int(round(start+Uk-ua))
        g,w,h=indices(i); y0=h//2
        for y in range(h):
            for x in range(w):
                u=x+SLOPE*(y-y0)+20
                if ua<=u<ub:
                    tx=x+dx
                    if 0<=tx<156 and ALPHA[g[y][x]]>=alpha[y][tx]:
                        out[y][tx]=g[y][x]; alpha[y][tx]=ALPHA[g[y][x]]
    if start<2 or start+total>154: print('WARN width',word,start,total)
    return out
def render(grid,scale=4):
    h=21;w=156
    im=Image.new('RGB',(w*scale,h*scale))
    d=ImageDraw.Draw(im)
    for y in range(h):
        for x in range(w):
            v=grid[y][x]; a=ALPHA[v]/255; I=INT[v]
            bg=(40,80,170)
            c=tuple(int(I*a+bg[k]*(1-a)) for k in range(3))
            d.rectangle([x*scale,y*scale,x*scale+scale-1,y*scale+scale-1],fill=c)
    return im
WORDS=["Play Game","Training","Roster","Contact","Pitching","Fielding","Pace","Complete","Game Time","Character","Color","Title","Encore","Grip"]
if __name__=='__main__':
    ims=[render(indices(57)[0])]+[render(compose(w)) for w in WORDS]
    sheet=Image.new('RGB',(156*4*2,21*4*8),(0,0,0))
    for k,im in enumerate(ims):
        sheet.paste(im,((k%2)*156*4,(k//2)*21*4))
    sheet.save('words.png')
