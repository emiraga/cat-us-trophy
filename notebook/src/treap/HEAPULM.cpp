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
const int N = 50000;
struct node
{
	string value; int weight, ch[2], size;
} T[ N+10 ] ;
int nodes;
#define Child(x,c) T[x].ch[c]
#define Value(x) T[x].value
#define Weight(x) T[x].weight
#define Left Child(x,0)
#define Right Child(x,1)
int newnode(string value, int prio)
{
	T[++nodes]=(node){value,prio,0,0};
	return nodes;
}
void print(int x)
{
	if(!x)return;
	printf("(");
	print(Left);
	printf("%s/%d",Value(x).c_str(),INT_MAX-Weight(x));
	print(Right);
	printf(")");
}
#define print(root) printf(""); print(root); printf("\n");
void rotate(int &x, int c)
{
	int y = Child(x,c);
	Child(x,c) = Child(y,!c);
	Child(y,!c) = x;
	x=y;
}
void insert(int &x, int n)
{
	if(!n) return;
	if(!x) { x=n; return; }
	int t = Value(n) > Value(x);
	insert(Child(x,t), n);
	if( Weight(Child(x,t)) < Weight(x)) rotate(x, t);
}
int find_GE(int x, string value)//node with Value greater or equal
{
	int ret=0;
	while(x)
	{
		if(Value(x)==value)return x;
		if(Value(x)>value) ret=x, x=Left; else x=Right;
	}
	return ret;
}
int find(int x, string value)//node with exact value
{
	for(; x; x=Child(x,Value(x)<value))
		if(Value(x)==value)return x;
	return 0;
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
int maxheight(int x)
{
	if(!x)return 0;
	return 1+max( maxheight(Left), maxheight(Right));
}
void split(int &x, int &leftT, int &rightT, string value)
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
int main()
{
	int n;
	while(scanf("%d",&n) == 1 && n)
	{
		vector<pair<string,int> >L;
		REP(__,n)
		{
			char a[3000];
			scanf("%s",a);
			int len=strlen(a); REP(i,len) if(a[i]=='/')a[i]=' ';
			string b; int c; istringstream sin(a);
			sin >> b >> c;
			L.push_back(make_pair(b,c));
		}
		sort(ALL(L));
		printf("()\n");
	}

	return 0;
}

