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
	int val;
} T[N];
#define Parent(x) T[x].p
#define Size(x) T[x].size
#define Left(x) T[x].l
#define Right(x) T[x].r
#define Value(x) T[x].val
int nodes;

void init(int x, int v)
{
	Left(x)=Right(x)=Parent(x)=0;
	Size(x)=1;
	Value(x)=v;
}

void update(int x)
{
	Size(x)= Size(Left(x)) + 1 + Size(Right(x));
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

// find node with Value(node) >= value
int find(int &root, int value)
{
	int x = root, ret = root;
	while(x)
	{
		if(Value(x) == value) return x;
		if(Value(x) > value) ret=x, x=Left(x); else x=Right(x);
	}
	return ret;
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
	return Size(Right(x));
}

int main()
{
	nodes=0;
	init(++nodes, INT_MIN);
	init(++nodes, INT_MAX);
	Left(2)=1; Parent(1)=2;
	update(2);
	int root=2;
//	print(root);printf("\n");
	int Q;scanf("%d",&Q);
	REP(i,Q)
	{
		char cmd[10];scanf("%s",cmd);
		int p; scanf("%d",&p);
//		D2(i,cmd);
		if(cmd[0]=='I') {
			int node = find(root,p);
			if(Value(node) != p)
				insertbefore(root, node, p);
			else
				splay(root,node);
		} else if(cmd[0]=='D') {
			int node = find(root,p);
			if(Value(node) == p)
				del(root, node);
			else
				splay(root,node);
		} else if(cmd[0]=='C') {
			int node = find(root,p);
			splay(root, node);
			printf("%d\n",Size(Left(root))-1);
		} else if(cmd[0]=='K') {
			if(p>Size(root)-2)
				printf("invalid\n");
			else
			{
				int node = findkth(root, p+1);
				splay(root,node);
				printf("%d\n",Value(node));
			}
		} else {
			printf("ERROR %s\n",cmd);
		}
//		print(root);printf("\n");
	}
	return 0;
}

