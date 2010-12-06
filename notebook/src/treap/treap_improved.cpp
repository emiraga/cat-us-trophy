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
#define D3(x,y,z) if(1) cout << __LINE__ <<" "<< #x " = " << (x) \
     <<", " << #y " = " << (y) \
     <<", " << #z " = " << (z) << endl;
const int N = 100 * 1000;
struct node { int value, weight, ch[2], size; } T[ N+10 ] ; int nodes;
#define Child(x,c) T[x].ch[c]
#define Value(x) T[x].value
#define Weight(x) T[x].weight
#define Size(x) T[x].size
#define Left Child(x,0)
#define Right Child(x,1)
int update(int x) { if(!x)return 0; Size(x) = 1 + Size(Left)+Size(Right); return x; }
int newnode(int value, int prio) {
	T[++nodes]=(node){value,prio,0,0};
	return update(nodes);
}
void split(int x, int by, int &L, int &R)
{
	if(!x) { L=R=0; }
	else if(Value(x) < Value(by)) { split(Right,by,Right,R); update(L=x); }
	else { split(Left,by,L,Left); update(R=x); }
}
int merge(int L, int R)
{
	if(!L) return R; if(!R) return L;
	if( Weight(L) < Weight(R) ) { Child(L,1) = merge(Child(L,1), R); return update(L); }
	else { Child(R,0) = merge( L, Child(R, 0)); return update(R); }
}
int insert(int x, int n)
{
	if(!x) { return update(n); }
	if(Weight(n) <= Weight(x)) { split(x,n,Child(n,0), Child(n,1)); return update(n); }
	else if(Value(n) < Value(x)) Left = insert(Left,n); else Right = insert(Right, n);
	return update(x);
}
int del(int x, int value)
{
	if(!x) return 0;
	if(value == Value(x)) { int q = merge(Left,Right); return update(q); }
	if(value < Value(x)) Left = del(Left,value); else Right = del(Right, value);
	return update(x);
}
int find_GE(int x, int value)
{
	int ret=0;
	while(x) {
		if(Value(x)==value)return x;
		if(Value(x)>value) ret=x, x=Left; else x=Right;
	}
	return ret;
}
int find(int x, int value)//node with exact value
{
	for(; x; x=Child(x,Value(x)<value))
		if(Value(x)==value)return x;
	return 0;
}
int findmin(int x) { for(;Left;x=Left); return x; }
int findmax(int x) { for(;Right;x=Right); return x; }
int findkth(int x, int k) {
	while(x) {
		if(k<=Size(Left)) x=Left;
		else if(k==Size(Left)+1)return x;
		else { k-=Size(Left)+1; x=Right; }
	} }
int queryrangekth(int &x, int a1, int a2, int k)
{
	a1 = find(x, a1);
	a2 = find(x, a2);
	assert(a1 && a2);
	int a,b,c;
	split(x,a1,a,b);
	split(b,a2,b,c);
	int ret = findkth(b,k);
	x = merge(a, merge(b,c));
	return Value(ret);
}
//not included
void print(int x)
{
	if(!x)return;
	if(Left) printf("["), print(Left), printf("]");
	printf("%d",Value(x),Weight(x));
	if(Right) printf("{"), print(Right), printf("}");
}
#define print(root) printf("List:"); print(root); printf("\n");
int maxheight(int x)
{
	if(!x)return 0;
	return 1+max( maxheight(Left), maxheight(Right));
}
int main()
{
	srand(time(NULL));
	int root=nodes=0;
	int n = 20;

	//special null node that has no size or childen
	assert(Child(0,0)==0 && Child(0,1)==0 && Size(0)==0);
	assert(n%2==0);
	FOR(i,1,n) root = insert(root,newnode(i,rand()));
	assert(Size(root) == n);
	FOR(i,1,n) assert(Value(find(root,i)) == i);

	FOR(i,1,n/2)
	{
		root = del(root, 2*i);
	}
	assert(Size(root) == n/2);
	FOR(i,1,n/2)
	{
		root = insert(root, newnode(2*i,rand()));
	}
	assert(Size(root) == n);
	FOR(i,1,n) assert(Value(find(root,i)) == i);
	FOR(i,1,n)
	{
		int x = findmin(root);
		assert(Value(x)==i);
		root = del(root,Value(x));
		assert(Size(root)== n - i);
	}
	assert(Size(root)==0);
	FOR(i,1,n) root = insert(root,newnode(i,rand()));
	assert(Size(root) == n);
	FOR(i,1,n)
	{
		root = del(root,Value(root));
		assert(Size(root) == n - i);
	}
	assert(root==0);
	FOR(i,1,n) root = insert(root,newnode(i,rand()));
	assert(Size(root) == n);
	D(maxheight(root));
	print(root);
	D(queryrangekth(root,4,5,1));
	print(root);
	FOR(i,1,20000)
	{
		int a=1+(rand()%n);
		int b=1+(rand()%n);
		if(a>b)swap(a,b);
		if(a==b) b++;
		if(b>n)continue;
		int k=1+rand()%(b-a);
		assert(queryrangekth(root, a,b,k) == a+k-1);
	}
	D(maxheight(root));
	return 0;
}

