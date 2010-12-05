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
const int N = 100 * 1000;
struct node
{
	int value, weight, ch[2], size;
} T[ N+10 ] ;
int nodes;
#define Child(x,c) T[x].ch[c]
#define Value(x) T[x].value
#define Weight(x) T[x].weight
#define Size(x) T[x].size
#define Left Child(x,0)
#define Right Child(x,1)
void update(int x)
{
	Size(x) = 1 + Size(Left)+Size(Right);
	//augmented data structure
}
int newnode(int value, int prio)
{
	T[++nodes]=(node){value,prio,0,0};
	update(nodes);
	return nodes;
}
void print(int x)
{
	if(!x)return;
	if(Left) printf("["), print(Left), printf("]");
	printf("%d",Value(x),Weight(x));
	if(Right) printf("{"), print(Right), printf("}");
}
#define print(root) printf("List:"); print(root); printf("\n");
void rotate(int &x, int c)
{
	int y = Child(x,c);
	Child(x,c) = Child(y,!c);
	Child(y,!c) = x;
	update(x);
	x=y;
}
void insert(int &x, int n)
{
	if(!n) return;
	if(!x) { x=n; return; }
	int t = Value(n) > Value(x);
	insert(Child(x,t), n);
	if( Weight(Child(x,t)) < Weight(x)) rotate(x, t);
	update(x);
}
int find_GE(int x, int value)//node with Value greater or equal
{
	int ret=0;
	while(x)
	{
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
void del(int &x, int value)//node with given value
{
	if(!x)return;
	if(value < Value(x)) { del(Left, value); update(x); return;}
	if(value > Value(x)) { del(Right, value); update(x); return;}
	if(Left || Right) rotate(x, Weight(Left) < Weight(Right)), del(x,value); else x=0;
}
int findmin(int x)//find node with min Value
{
	for(;Left;x=Left);
	return x;
}
int findmax(int x)//find node with max Value
{
	for(;Right;x=Right);
	return x;
}
int findkth(int x, int k)
{
	while(x)
	{
		if(k<=Size(Left)) x=Left;
		else if(k==Size(Left)+1)return x;
		else { k-=Size(Left)+1; x=Right; }
	}
}
int maxheight(int x)
{
	if(!x)return 0;
	return 1+max( maxheight(Left), maxheight(Right));
}
void split(int &x, int &leftT, int &rightT, int value)
{
	insert(x, newnode(value, INT_MIN));
	leftT=Left;
	rightT=Right;
}
void join(int &x, int leftT, int rightT)
{
	insert(leftT, rightT);
	x = leftT;
}
int queryrangekth_old_version(int &root, int a, int b, int k)
{
	int l,m,r;
	split(root, l, m, a);
	int root2 = m;
	split(root2, m, r, b);
	int ret = findkth(m,k);
	join(root2, l, m);
	join(root, root2, r);
	return ret;
}
int queryrangekth(int &x, int a, int b, int k)
{
	insert(x, newnode(a, INT_MIN+1));
	insert(x, newnode(b, INT_MIN));
	int ret = findkth(Child(Left,1),k);
	int root = Child(Left,0);
	insert(root, Child(Left,1));
	insert(root, Right);
	x=root;
	return ret;
}
int main()
{
	int root=nodes=0;
	int n = 50;

	//special null node that has no size or childen
	assert(Child(0,0)==0 && Child(0,1)==0 && Size(0)==0);

	assert(n%2==0);
	FOR(i,1,n) insert(root,newnode(i,rand()));
	assert(Size(root) == n);
	FOR(i,1,n) assert(Value(find(root,i)) == i);

	FOR(i,1,n/2) del(root, 2*i);
	assert(Size(root) == n/2);
	
	FOR(i,1,n/2) insert(root, newnode(2*i,rand()));
	assert(Size(root) == n);
	FOR(i,1,n) assert(Value(find(root,i)) == i);
	
	FOR(i,1,n)
	{
		int x = findmin(root);
		assert(Value(x)==i);
		del(root,Value(x));
		assert(Size(root)== n - i);
	}
	assert(Size(root)==0);
	FOR(i,1,n) insert(root,newnode(i,rand()));
	assert(Size(root) == n);
	FOR(i,1,n)
	{
		del(root,Value(root));
		assert(Size(root) == n - i);
	}
	assert(root==0);
	FOR(i,1,n) insert(root,newnode(i,rand()));
	D(maxheight(root));
	FOR(i,1,2000)
	{
		int a=1+(rand()%n);
		int b=1+(rand()%n);
		if(a>b)swap(a,b);
		int k=(a!=b)?1+rand()%(b-a):1;
		assert(Value(queryrangekth(root, a,b+1,k))==a+k-1);
		D(maxheight(root));
	}
	D(maxheight(root));
	return 0;
}

