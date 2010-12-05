
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

int N,Que,root,tot,cnt,x,y;
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
inline int Tjoin(int u,int v)
{
    if (!u)    return v;
    if (!v)    return u;
    int p=u;
    for (;Rch(p);p=Rch(p));
    splay(u,p);
    return Rch(p)=v,Par(v)=p,p;
}
inline void D(int x)
{
    splay(root,x);
    Par(Lch(x))=Par(Rch(x))=0;
    root=Tjoin(Lch(x),Rch(x));
    Tupdate(root);
}
inline void I(int x,int y)
{
    splay(root,x);
    int v=Lch(x);
    for (;Rch(v);v=Rch(v));
    Rch(v)=++tot,Par(tot)=v,Size(tot)=1;
    Sum(tot)=Ms(tot)=Lms(tot)=Rms(tot)=Val(tot)=y;
    splay(root,tot);
}
inline void R(int x,int y)
{
    Val(x)=y;
    splay(root,x);
}
inline void Q(int x,int y)
{
    splay(root,y);
    Par(Lch(y))=0;
    splay(Lch(y),x);
    Par(x)=y;
    printf("%d\n",Ms(Rch(x)));
}

void print_r(int node)
{
	if(!node) { printf("()"); return; }
	printf("(");
	print_r( Lch(node) );
	printf(" %d ",Val(node));
	print_r( Rch(node) );
	printf(")");
}

void print_l(int node)
{
	if(!node) { printf("XX"); return; }
	printf(" %d ",Val(node));
	printf("(");
	print_l( Lch(node) );
	printf(",");
	print_l( Rch(node) );
	printf(")");
}

int main()
{
    scanf("%d",&N);
    for (int i=1;i<=N;++i)
    {
        scanf("%d",&Val(i));
        Sum(i)=Ms(i)=Lms(i)=Rms(i)=Val(i);
        Par(i)=i-1,Rch(i-1)=i,Size(i)=N-i+1;
        splay(root,i);
    }
    splay(root,1),Par(N+1)=1,Lch(1)=N+1,Size(N+1)=1,splay(root,N+1);
    splay(root,N),Par(N+2)=N,Rch(N)=N+2,Size(N+2)=1,splay(root,N+2);
    tot=N+2;
    for (scanf("%d",&Que);Que--;)
    {
        scanf("%s%d",cmd,&x);
        if (cmd[0]=='D')    D(Findkth(root,x+1));
        else
        {
            scanf("%d",&y);
            if (cmd[0]=='Q')    Q(Findkth(root,x),Findkth(root,y+2));
            else
            if (cmd[0]=='I')    I(Findkth(root,x+1),y);
            else    R(Findkth(root,x+1),y);
        }
    }
	print_r(root); printf("\n");
	print_l(root); printf("\n");
    return 0;
}

//(((() 0 ((() 3 (() -4 (() 3 ()))) -1 ())) 6 ()) 0 ())
// 0 ( 6 ( 0 (XX, -1 ( 3 (XX, -4 (XX, 3 (XX,XX))),XX)),XX),XX)

//((() 0 ((() 3 ()) -1 (() 3 ((() -1 (() -4 ())) 2 ())))) 0 ())
// 0 ( 0 (XX, -1 ( 3 (XX,XX), 3 (XX, 2 ( -1 (XX, -4 (XX,XX)),XX)))),XX)

