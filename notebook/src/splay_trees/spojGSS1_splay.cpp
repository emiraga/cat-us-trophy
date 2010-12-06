#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <complex>
#include <cctype>
#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <map>
#include <set>
using namespace std;
template<class T> inline void checkmin(T &a, const T &b) { if(a > b) a = b; }
template<class T> inline void checkmax(T &a, const T &b) { if(a < b) a = b; }
#define Dhelper(X) " " << #X << "='" << (X) << "'"
#define D(X) {cerr << __LINE__ << ":" << Dhelper(X) << endl;}
#define D2(X,Y) {cerr << __LINE__ << ":" << Dhelper(X) << Dhelper(Y) << endl;}
#define D3(X,Y,Z) {cerr << __LINE__ << ":" <<Dhelper(X)<<Dhelper(Y)<<Dhelper(Z)<< endl;}
#define D4(X,Y,Z,W) {cerr << __LINE__ << ":" <<Dhelper(X)<<Dhelper(Y)<<Dhelper(Z)<<Dhelper(W)<< endl;}
#define D5(X,Y,Z,W,V) {cerr << __LINE__ << ":"<<Dhelper(X)<<Dhelper(Y)<<Dhelper(Z)<<Dhelper(W)<<Dhelper(V)<< endl;}
#define Dv(X) {cerr << __LINE__ << ":  " << #X << " = {"; for(int __i=0;__i<(X).size();__i++) cerr<<" "<<(X)(__i);cerr<<" }"<<endl;}
#define Da(X,n) {cerr << __LINE__ << ":  " << #X << " = {"; for(int __i=0;__i<(n);__i++) cerr<<" "<<(X)(__i);cerr<<" }"<<endl;}
#define Rep(i, n) for(int i = 0; i < (n); ++i)
#define Repe(i, n) for(int i = 0; i <= (n); ++i)
#define For(i,a,b) for(int i=(a); i<(b); i++)
#define Fore(i,a,b) for(int i=(a); i<=(b); i++)
#define Ford(i,a,b) for(int i=(a); i>=(b); i--)
#define Foreach(it,X) for(__typeof((X).begin())it=(X).begin();it!=(X).end();++it)

const int MAXN = 2 * 100 * 1000 + 100;

struct splay{
	int left,right,parent,value,lb,rb,best,size,sum;
} TT[MAXN];

#define Left(x) TT[x].left
#define Right(x) TT[x].right
#define Parent(x) TT[x].parent
#define Value(x) TT[x].value
#define leftBest(x) TT[x].lb
#define rightBest(x) TT[x].rb
#define Best(x) TT[x].best
#define Size(x) TT[x].size
#define Sum(x) TT[x].sum

inline void Tupdate(int x)
{
	//update this position
	Size(x)=Size(Left(x)) + 1 + Size(Right(x));
	Sum(x)=Sum(Left(x)) + Value(x) + Sum(Right(x));
	leftBest(x) = max(  leftBest( Left(x) ) , Sum(Left(x)) + Value(x) + leftBest(Right(x)) );
	rightBest(x) = max(  rightBest( Right(x) ) , Sum(Right(x)) + Value(x) + rightBest(Left(x)) );
	Best(x) = rightBest(Left(x)) + Value(x) + leftBest(Right(x));
	if(Left(x)) checkmax(Best(x), Best(Left(x)));
	if(Right(x)) checkmax(Best(x), Best(Right(x)));
}

inline void zig(int x)
{
	int y=Parent(x),z=Parent(y);
	Left(y)=Right(x),Parent(Left(y))=Right(x)=y;
	if (Left(z)==y) Left(z)=x; else Right(z)=x;
	Parent(x)=z,Parent(y)=x;
	Tupdate(y);
}

inline void zag(int x)
{
	int y=Parent(x),z=Parent(y);
	Right(y)=Left(x),Parent(Right(y))=Left(x)=y;
	if (Left(z)==y) Left(z)=x; else Right(z)=x;
	Parent(x)=z,Parent(y)=x;
	Tupdate(y);
}

inline void splay(int &root, int x)
{
	for (int y,z;Parent(x);)
	{
		y=Parent(x),z=Parent(y);
		if (!z)
			if (Left(y)==x) zig(x); else zag(x);
		else if (Left(z)==y)
			if (Left(y)==x) zig(y),zig(x); else zag(x),zig(x);
		else
			if (Right(y)==x) zag(y),zag(x); else zig(x),zag(x);
	}
	Tupdate(root=x);
}

/*void insert(int &root, int value)
{
	int node=root, add=1;
	while(add)
		if(Value(node) > value)
			if(Left(node)) node=Left(node); else Left(node)=++num,add=0;
		else
			if(Right(node)) node=Right(node); else Right(node)=++num,add=0;
	Parent(num) = node;
	Value(num) = value;
	splay(root, num);
}*/

void print_l(int node)
{
	printf(" %d ", Value(node));
	printf("(");
	if(Left(node))
	{
		assert(Parent(Left(node)) == node);
		print_l( Left(node) );
	}
	else
		printf("XX"); 
	printf(",");
	if(Right(node))
	{
		assert(Parent(Right(node)) == node);
		print_l( Right(node) );
	}
	else
		printf("XX"); 
	printf(")");
}

int findkth(int &root, int k)
{
	int p = root;
	while(1)
	{
		if(k <= Size(Left(p)))
		{
			p = Left(p);
		} else if(k <= Size(Left(p)) + 1) {
			//splay(root, p);
			return p;
		} else {
			k -= Size(Left(p))+1;
			p = Right(p);
		}
	}
}

int query(int &root, int n1, int n2)
{
	splay(root, n2); 
	Parent(Left(n2)) = 0;
	splay(Left(n2), n1);
	Parent(n1) = n2;
	return Best(Right(n1));
}

int main()
{
	int root = 1;
	
	int N;
	scanf("%d",&N);
	Fore(i,2,N+1) scanf("%d",&Value(i));
	Fore(i,2,N+2) Right(i-1) = i, Parent(i) = i-1;
	Ford(i,N+2,1) Tupdate(i);

	int Q; scanf("%d",&Q);
	Rep(__,Q)
	{
		int a, b; scanf("%d %d", &a, &b);
		b+=2;
		//D2(a, findkth(root, a));
		//D2(b, findkth(root, b));
		printf("%d\n", query(root, findkth(root, a), findkth(root, b)));
	}
	return 0;
}


