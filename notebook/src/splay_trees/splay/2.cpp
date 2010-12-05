//
#include <cstdio>
#define max(a,b) ((a)>(b)?(a):(b))
struct Tsplay
{
    #define Lch(x)    T[x].l
    #define Rch(x)    T[x].r
    #define Par(x)    T[x].p
    #define Val(x)    T[x].val
    #define Sum(x)    T[x].sum
    #define Lms(x)    T[x].lms
    #define Rms(x)    T[x].rms
    #define Ms(x)    T[x].ms
    #define Size(x)    T[x].size
    int l,r,p,size;
    int    sum,ms,lms,rms,val;
}    T[200005];

int N,Que,root,cnt,x,y;
char cmd[105];

inline void Tupdate(int x)
{
    Size(x)=Size(Lch(x))+1+Size(Rch(x));
    Sum(x)=Sum(Lch(x))+Val(x)+Sum(Rch(x));
    Lms(x)=max(Lms(Lch(x)),Sum(Lch(x))+Val(x)+Lms(Rch(x)));
    Rms(x)=max(Rms(Rch(x)),Rms(Lch(x))+Val(x)+Sum(Rch(x)));
    Ms(x)=Rms(Lch(x))+Val(x)+Lms(Rch(x));
    if (Lch(x))    Ms(x)=max(Ms(x),Ms(Lch(x)));
    if (Rch(x))    Ms(x)=max(Ms(x),Ms(Rch(x)));
}
inline void zig(int x)
{
    int y=Par(x),z=Par(y);
    Lch(y)=Rch(x),Par(Lch(y))=Rch(x)=y;
    if (Lch(z)==y)    Lch(z)=x;
    else    Rch(z)=x;
    Par(x)=z,Par(y)=x;
    Tupdate(y);
}
inline void zag(int x)
{
    int y=Par(x),z=Par(y);
    Rch(y)=Lch(x),Par(Rch(y))=Lch(x)=y;
    if (Lch(z)==y)    Lch(z)=x;
    else    Rch(z)=x;
    Par(x)=z,Par(y)=x;
    Tupdate(y);
}
inline void splay(int &root,int x)
{
    for (int y,z;Par(x);)
    {
        y=Par(x),z=Par(y);
        if (!z)
            if (Lch(y)==x)    zig(x);
            else    zag(x);
        else
        if (Lch(z)==y)
            if (Lch(y)==x)    zig(y),zig(x);
            else    zag(x),zig(x);
        else
            if (Rch(y)==x)    zag(y),zag(x);
            else    zig(x),zag(x);
    }
    Tupdate(root=x);
}
inline int Findkth(int root,int k)
{
    for (int p=root;;)
    if (k<=Size(Lch(p)))    p=Lch(p);
    else
    if (k<=Size(Lch(p))+1)    return p;
    else    k-=Size(Lch(p))+1,p=Rch(p);
}
inline void Q(int x,int y)
{
    splay(root,y);
    Par(Lch(y))=0;
    splay(Lch(y),x);
    Par(x)=y;
    printf("%d\n",Ms(Rch(x)));
}
int main()
{
    scanf("%d",&N);
	root = 1;
	for(int i=2;i<=N+1;i++) scanf("%d",&Val(i));
	for(int i=2;i<=N+2;i++) Rch(i-1) = i, Par(i) = i-1;
	for(int i=N+2;i>=1;i--) Tupdate(i);

    for (scanf("%d",&Que);Que--;)
    {
		scanf("%d",&x);
        scanf("%d",&y);
        Q(Findkth(root,x),Findkth(root,y+2));
    }
    return 0;
}

