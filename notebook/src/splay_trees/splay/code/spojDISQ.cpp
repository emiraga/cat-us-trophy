#include <cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define n 100005
struct Tsplay
{
    #define Lch(x)    T[x].l
    #define Rch(x)    T[x].r
    #define Par(x)    T[x].p
    #define Max(x)    T[x].max
    #define Min(x)    T[x].min
    #define Val(x)    T[x].val
    #define Root(x)    (Lch(Par(x))!=x&&Rch(Par(x))!=x)
    int l,r,p;
    int max,min,val;
}    T[n];
int vtx[200005],ne[200005],w[200005],L[n],q[n],tot;
int N,Q;
bool vis[100005];
inline void Ins(int u,int v,int ww)
{
    vtx[++tot]=v;w[tot]=ww;ne[tot]=L[u];L[u]=tot;
}
inline void BuildTree()
{
    vis[q[1]=1]=1;
    for (int h=1,t=1,u=q[h];h<=t;u=q[++h])
    for (int p=L[u],v=vtx[p];p;v=vtx[p=ne[p]])
    if (!vis[v])
    {
        Par(v)=u,Val(v)=w[p];
        vis[q[++t]=v]=1;
    }
}
inline void Tupdate(int x)
{
    Min(x)=Max(x)=Val(x);
    if (Lch(x))
    {
        Min(x)=min(Min(x),Min(Lch(x)));
        Max(x)=max(Max(x),Max(Lch(x)));
    }
    if (Rch(x))
    {
        Min(x)=min(Min(x),Min(Rch(x)));
        Max(x)=max(Max(x),Max(Rch(x)));
    }
}
inline void zig(int x)
{
    int y=Par(x),z=Par(y);
    Lch(y)=Rch(x);
    Par(Lch(y))=Rch(x)=y;
    if (Lch(z)==y)    Lch(z)=x;
    else
    if (Rch(z)==y)    Rch(z)=x;
    Par(x)=z,Par(y)=x;
    Tupdate(y);
}
inline void zag(int x)
{
    int y=Par(x),z=Par(y);
    Rch(y)=Lch(x);
    Par(Rch(y))=Lch(x)=y;
    if (Lch(z)==y)    Lch(z)=x;
    else
    if (Rch(z)==y)    Rch(z)=x;
    Par(x)=z,Par(y)=x;
    Tupdate(y);
}
inline void splay(int x)
{
    for (int y,z;!Root(x);)
    {
        y=Par(x),z=Par(y);
        if (Root(y))
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
    Tupdate(x);
}
inline void Expose(int x)
{
    for (int u=x,v=0;u;u=Par(u))
        splay(u),Rch(u)=v,Tupdate(v=u);
}
inline void Query(int x,int y)
{
    Expose(x);
    for (int u=y,v=0,vmax,vmin;u;u=Par(u))
    {
        if (splay(u),!Par(u))
        {
            vmax=-(1<<30),vmin=(1<<30);
            if (v)    vmin=min(vmin,Min(v)),vmax=max(vmax,Max(v));
            if (Rch(u))    vmin=min(vmin,Min(Rch(u))),vmax=max(vmax,Max(Rch(u)));
            printf("%d %d\n",vmin,vmax);
            return;
        }
        Rch(u)=v,Tupdate(v=u);
    }
}
int main()
{
    int x,y,w;
    scanf("%d",&N);
    for (int i=1;i<N;++i)
        scanf("%d%d%d",&x,&y,&w),Ins(x,y,w),Ins(y,x,w);
    BuildTree();
    for (scanf("%d",&Q);Q--;)
    {
        scanf("%d%d",&x,&y);
        Query(x,y);
    }
    return 0;
}
