/*
ID: emiraga1
LANG: C++
TASK: 
*/
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
#define FOR(i,a,b) for( __typeof(a) i=(a); i<=(b); i++)
#define FORD(i,a,b) for(__typeof(a) i=(a); i>=(b); i--) 
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define SET(t,v) memset((t), (v), sizeof(t))
#define ALL(x) x.begin(), x.end()
#define REV(x) reverse( ALL( x ) )
#define UNIQUE(c) (c).resize( unique( ALL(c) ) - (c).begin() )

#define sz size()
#define pb push_back
#define VI vector<int>
#define VS vector<string>
typedef long long i64;
typedef long long LL;
typedef long double LD;

#define D(x) if(1) cerr << __LINE__ <<" "<< #x " = " << x << endl
#define D2(x,y) if(1) cerr << __LINE__ <<" "<< #x " = " << x \
	<<", " << #y " = " << y << endl

#define IO freopen(".in","rb",stdin);freopen(".out","wb",stdout);

int n;
typedef pair<int, int>pdd;
#define x first
#define y second
#define sq(o) ((o)*(o))

pdd p[110];

int main() {
    while(scanf("%d",&n) == 1 && n)
	{
		REP(i,n)
		{
			scanf("%d %d",&p[i].x,&p[i].y);
		}
		int res = min(2,n);
		REP(a,n)
		{
			int dx=p[a].x;
			int dy=p[a].y;
			REP(i,n)
			{
				p[i].x -= dx;
				p[i].y -= dy;
			}
			FOR(b,a+1,n-1)
			{
				vector<double> radii;
				REP(c,n)
				{
					if(a==c || b==c)continue;
#define A p[a]
#define B p[b]
#define C p[c]
double d=2*(B.x*C.y-C.x*B.y);
if(fabs(d) < 1e-11)continue;
double x1=((B.y*B.y+B.x*B.x)*C.y-(C.y*C.y+C.x*C.x)*B.y)/d;
double y1=((C.x*C.x+C.y*C.y)*B.x-(B.x*B.x+B.y*B.y)*C.x)/d;
double r = (sq(x1) + sq(y1));
double ang = (B.x)*(y1) - (B.y)*(x1);
					if(ang < 0) radii.pb(-r); else radii.pb(r);
				}
				sort(ALL(radii));
				int c = 3;
//				D(radii.sz);
//				printf("Rad:");
//				REP(i,radii.sz)printf("%lf ",radii[i]);
//				printf("\n");
				int m = int(radii.sz)-1;
				FOR(i,1,m)
				{
					if(fabs(radii[i] - radii[i-1]) < 1e-11)
						c++;
					else
					{
						c = 3;
					}
					res = max(res, c);
				}
			}
		}
		printf("%d\n",res);
	}
    return 0;
}

