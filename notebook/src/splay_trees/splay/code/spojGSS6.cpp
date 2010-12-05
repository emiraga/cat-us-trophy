#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<stack>
#include<list>
#include<iostream>
#include<fstream>
#include<numeric>
#include<string>
#include<vector>
#include<cstring>
#include<map>
#include<iterator>
#include<ctime>
#include<cassert>
#include<climits>
using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define FORD(i,a,b) for(int i=(a); i>=(b); i--) 
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define SET(t,v) memset((t), (v), sizeof(t))
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize( unique( ALL(c) ) - (c).begin() )

#define sz(v) int(v.size())
#define pb push_back
#define VI vector<int>
#define VS vector<string>

typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;

#define D(x) if(1) cout << __LINE__ <<" "<< #x " = " << (x) << endl;
#define D2(x,y) if(1) cout << __LINE__ <<" "<< #x " = " << (x) \
     <<", " << #y " = " << (y) << endl;
const int N = 200 * 1000;
struct node
{
	int l,r,p,size;
	int val, maximum;
	int lmax,rmax,sum;
} T[N];
#define Parent(x) T[x].p
#define Size(x) T[x].size
#define Left(x) T[x].l
#define Right(x) T[x].r
#define Value(x) T[x].val
#define Maximum(x) T[x].maximum
#define Lmax(x) T[x].lmax
#define Rmax(x) T[x].rmax
#define Sum(x) T[x].sum
int nodes;

void init(int x, int v)
{
	Left(x)=Right(x)=Parent(x)=0;
	Size(x)=1;
	Maximum(x)=Value(x)=Sum(x)=Lmax(x)=Rmax(x)=v;
}

void update(int x)
{
	Size(x)= Size(Left(x)) + 1 + Size(Right(x));
	Sum(x)= Sum(Left(x)) + Value(x) + Sum(Right(x));
	Lmax(x) = max(Lmax(Left(x)), Sum(Left(x)) + Value(x) + max(0,Lmax(Right(x)) ));
	Rmax(x) = max(Rmax(Right(x)), Sum(Right(x)) + Value(x) + max(0,Rmax(Left(x)) ));
	Maximum(x) = Value(x) + max(0,Rmax(Left(x)))+max(0,Lmax(Right(x)));
	if(Left(x)) Maximum(x) = max( Maximum(x), Maximum(Left(x)));
	if(Right(x)) Maximum(x) = max( Maximum(x), Maximum(Right(x)));
}

void zig(int x)
{
	int y=Parent(x), z=Parent(y);
	Left(y)=Right(x), Parent(Left(y))=Right(x)=y;
	if(Left(z)==y) Left(z)=x; else Right(z)=x;
	Parent(x)=z, Parent(y)=x;
	update(y);
}

void zag(int x)
{
	int y=Parent(x), z=Parent(y);
	Right(y)=Left(x), Parent(Right(y))=Left(x)=y;
	if(Left(z)==y) Left(z)=x; else Right(z)=x;
	Parent(x)=z, Parent(y)=x;
	update(y);
}

void splay(int &root, int x)
{
	while(Parent(x))
	{
		int y=Parent(x), z=Parent(y);
		if(z) if(Left(z)==y) if(Left(y)==x) zig(y),zig(x);else zag(x),zig(x);
		               else if(Right(y)==x) zag(y),zag(x);else zig(x),zag(x);
		else if(Left(y)==x) zig(x); else zag(x);
	}
	update(root=x);
}

int findkth(int p, int k)
{
	while(1)
	{
		if(k<=Size(Left(p))) p = Left(p);
		else if(k==Size(Left(p))+1)return p;
		else k-=Size(Left(p))+1, p=Right(p);
	}
}

int join(int u, int v)
{
	if(!u) return v;
	if(!v) return u;
	int p;
	for(p=u;Right(p);p=Right(p));
	splay(u,p);
	Right(p)=v; Parent(v)=p;
	return p;
}

void del(int &root, int x)
{
	splay(root,x);
	Parent(Left(x))=Parent(Right(x))=0;
	root=join(Left(x), Right(x));
	update(root);
}

void print(int x)
{
	if(Left(x)) {
		printf("[");
		print(Left(x));
		printf("]");
	}
	printf("%d",Value(x));
	if(Right(x))
	{
		printf("{");
		print(Right(x));
		printf("}");
	}
}

void insertbefore(int &root, int x, int value)
{
	splay(root,x);
	int v;
	for(v=Left(x);Right(v);v=Right(v));
	int n = ++nodes;
	init(n, value);
	Right(v)=n; Parent(n)=v;
	update(v);
	splay(root, n);
}

void replace(int &root, int x, int value)
{
	splay(root,x);
	Value(x)=value;
	update(x);
}

int query(int &root, int x, int y)
{
	splay(root,y);
	Parent(Left(y))=0;
	splay(Left(y), x);
	Parent(x)=y;
	return Maximum(Right(x));
}

int main()
{
	int N;scanf("%d",&N);
	nodes=0;
	init(++nodes, INT_MIN);
	FOR(i,1,N)
	{
		int v; scanf("%d",&v);
		init(++nodes, v);
	}
	init(++nodes, INT_MIN);
	FOR(i,2,nodes)
	{
		Left(i) = i-1; Parent(i-1) = i;
		update(i);
	}
	int root=nodes;
	splay(root,1);
	int Q;scanf("%d",&Q);
	REP(i,Q)
	{
		char cmd[10];scanf("%s",cmd);
		if(cmd[0]=='I')
		{
			int p,v; scanf("%d %d",&p, &v);
			insertbefore(root, findkth(root,p+1),v);
		} else if(cmd[0]=='D') {
			int p; scanf("%d",&p);
			del(root, findkth(root,p+1));
		} else if(cmd[0]=='R') {
			int p,v; scanf("%d %d",&p,&v);
			replace(root, findkth(root,p+1),v);
		} else if(cmd[0]=='Q') {
			int a,b; scanf("%d %d",&a, &b);
			int r = query(root,findkth(root,a+0),findkth(root,b+2));
			printf("%d\n",r);
		} else {
			printf("ERROR %s\n",cmd);
		}
	}
	return 0;
}

