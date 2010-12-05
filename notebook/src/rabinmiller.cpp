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

LL mulmod(LL a,LL b,LL c){
	LL x=0,y=a%c;
	for(;b;b/=2){
		if(b%2) x = (x+y)%c;
		y = (y+y)%c;
	}
	return x;
}
LL expmod(LL a, LL b, LL c){
	LL x=1,y=a%c;
	for(;b;b/=2){
		if(b%2) x=mulmod(x,y,c);
		y = mulmod(y,y,c);
	}
	return x;
}

bool Miller(LL p, int a){
	if(p<2) return 0;
	if(p%2==0) return p==2;
	if(p==a) return 1;
	LL s=p-1;
	while(s%2==0) s/=2;
	LL mod=expmod(a,s,p);
	for(;s-p+1 && mod-1 && mod-p+1;s*=2) mod=mulmod(mod,mod,p);
	return mod==p-1 || s%2;
}

bool isprime(LL n)
{
	return Miller(n,2) && Miller(n,7) && Miller(n,61);
}

bool isprime2(LL n)
{
	if(n<2) return 0;
	if(n%2==0) return n==2;
	for(LL i=3;i*i<=n;i+=2)
		if(n%i==0)return 0;
	return 1;
}

int main()
{
	for(LL j=0;;j+=100000)
	{
		D(j);
		REP(i,100000)
		{
			assert(isprime(j+i) == isprime2(j+i));
		}
	}
	return 0;
}

