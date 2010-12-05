#include <cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define n 100005
struct Tsplay
{
    #define Left(x)    T[x].l
    #define Right(x)    T[x].r
    #define Parent(x)    T[x].p
    #define Max(x)    T[x].max
    #define Min(x)    T[x].min
    #define Val(x)    T[x].val
    #define isRoot(x)    (Left(Parent(x))!=x&&Right(Parent(x))!=x)
    int l,r,p;
    int max,min,val;
} T[n];
int edgeto[200005];
int next[200005];
int weight[200005];
int first[n];
int list[n];
int total;
bool visited[100005];

inline void Addedge(int u,int v,int ww)
{
    edgeto[++total]=v;
	weight[total]=ww;
	next[total]=first[u];
	first[u]=total;
}
inline void BuildTree()
{
	list[1]=1;
	visited[1]=1;
	for (int h=1,t=1; h<=t; h++)
	{
		int u = list[h];
		for (int p=first[u]; p; p=next[p])
		{
			int v = edgeto[p];
			if (!visited[v])
			{
				printf("parent of %d is %d\n",v,u);
				Parent(v)=u;
				Val(v) = weight[p];
				list[++t] = v;
				visited[v]=1;
			}
		}
	}
}
inline void Tupdate(int x)
{
    Min(x)=Max(x)=Val(x);
    if (Left(x))
    {
        Min(x)=min(Min(x),Min(Left(x)));
        Max(x)=max(Max(x),Max(Left(x)));
    }
    if (Right(x))
    {
        Min(x)=min(Min(x),Min(Right(x)));
        Max(x)=max(Max(x),Max(Right(x)));
    }
}
inline void zig(int x)
{
    int y=Parent(x),z=Parent(y);
    Left(y)=Right(x);
    Parent(Left(y))=Right(x)=y;
    if (Left(z)==y)    Left(z)=x;
    else
    if (Right(z)==y)    Right(z)=x;
    Parent(x)=z,Parent(y)=x;
    Tupdate(y);
}
inline void zag(int x)
{
    int y=Parent(x),z=Parent(y);
    Right(y)=Left(x);
    Parent(Right(y))=Left(x)=y;
    if (Left(z)==y)    Left(z)=x;
    else
    if (Right(z)==y)    Right(z)=x;
    Parent(x)=z,Parent(y)=x;
    Tupdate(y);
}
inline void splay(int x)
{
    for (int y,z;!isRoot(x);)
    {
        y=Parent(x),z=Parent(y);
        if (isRoot(y))
            if (Left(y)==x)    zig(x);
            else    zag(x);
        else
        if (Left(z)==y)
            if (Left(y)==x)    zig(y),zig(x);
            else    zag(x),zig(x);
        else
            if (Right(y)==x)    zag(y),zag(x);
            else    zig(x),zag(x);
    }
    Tupdate(x);
}
void printn_1(int x)
{
	if(!x)return;
	if(Left(x)){ printf("["); printn_1(Left(x)); printf("]"); }
	printf("%d",x);
	if(Right(x)){ printf("{"); printn_1(Right(x)); printf("}"); }
}
void printn(int x, char c = 'L')
{
	printf("%c: ",c);
	printn_1(x);
	printf("\n");
}
inline void Expose(int x)
{
	int v=0;
    for (int u=x;u;u=Parent(u))
        splay(u),Right(u)=v,Tupdate(v=u);
	printn(v);
}
inline void Query(int x,int y)
{
    Expose(x);
	int v=0;
    for (int u=y;u;u=Parent(u))
    {
		splay(u);
        if (!Parent(u))
        {
			printn(u,'u');
			printn(v,'v');
            int vmax=-(1<<30),vmin=(1<<30);
            if (v)    vmin=min(vmin,Min(v)),vmax=max(vmax,Max(v));
            if (Right(u))    vmin=min(vmin,Min(Right(u))),vmax=max(vmax,Max(Right(u)));
            printf("%d %d\n",vmin,vmax);
            return;
        }
        Right(u)=v,Tupdate(v=u);
    }
}
int N,Q;
int main()
{
    int x,y,weight;
    scanf("%d",&N);
    for (int i=1;i<N;++i)
        scanf("%d%d%d",&x,&y,&weight),Addedge(x,y,weight),Addedge(y,x,weight);
    BuildTree();
    for (scanf("%d",&Q);Q--;)
    {
        scanf("%d%d",&x,&y);
		printf("x=%d  y=%d\n",x,y);
        Query(x,y);
    }
    return 0;
}

