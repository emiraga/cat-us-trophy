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
#include<string>
#include<vector>
#include<cstring>
#include<map>
#include<cassert>
#include<climits>
using namespace std;

#define REP(i,n) for(int i=0, _e(n); i<_e; i++)
#define FOR(i,a,b) for(int i(a), _e(b); i<=_e; i++)
#define FORD(i,a,b) for(int i(a), _e(b); i>=_e; i--) 
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define SET(t,v) memset((t), (v), sizeof(t))
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize( unique( ALL(c) ) - (c).begin() )

#define sz size()
#define pb push_back
#define VI vector<int>
#define VS vector<string>

typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;

#define D(x) if(1) cout << __LINE__ <<" "<< #x " = " << (x) << endl;
#define D2(x,y) if(1) cout << __LINE__ <<" "<< #x " = " << (x) \
	<<", " << #y " = " << (y) << endl;

typedef vector<VI> VVI;
#define SZ(x) ((x).size())
#define PB push_back

int N;

VI match;
VI vis;

void couple(int n, int m) { match[n]=m; match[m]=n; }

// returns true if something interesting has been found, thus a
// augmenting path or a blossom (if blossom is non-empty).
// the dfs returns true from the moment the stem of the flower is
// reached and thus the base of the blossom is an unmatched node.
// blossom should be emty when dfs is called and 
// contains the nodes of the blossom when a blossom is found.
bool dfs(int n, VVI &conn, VI &blossom) {
	vis[n]=0;
	REP(i, N)
	{
		if(conn[n][i])
		{
			if(vis[i]==-1) {
				vis[i]=1;
				if(match[i]==-1 || dfs(match[i], conn, blossom)) { couple(n,i); return true; }
			}
			if(vis[i]==0 || SZ(blossom)) {  // found flower
				blossom.PB(i); blossom.PB(n);
				if(n==blossom[0]) { match[n]=-1; return true; }
				return false;
			}
		}
	}
	return false;
}

// search for an augmenting path.
// if a blossom is found build a new graph (newconn) where the
// (free) blossom is shrunken to a single node and recurse.
// if a augmenting path is found it has already been augmented
// except if the augmented path ended on the shrunken blossom.
// in this case the matching should be updated along the appropriate
// direction of the blossom.
bool augment(VVI &conn)
{
	REP(m, N)
	{
		if(match[m]==-1)
		{
			VI blossom;
			vis=VI(N,-1);
			if(!dfs(m, conn, blossom)) continue;
			if(SZ(blossom)==0) return true; // augmenting path found

			// blossom is found so build shrunken graph
			int base=blossom[0], S=SZ(blossom);
			VVI newconn=conn;
			FOR(i, 1, S-1) REP(j, N) newconn[base][j]=newconn[j][base]|=conn[blossom[i]][j];
			FOR(i, 1, S-1) REP(j, N) newconn[blossom[i]][j]=newconn[j][blossom[i]]=0;
			newconn[base][base]=0; // is now the new graph
			if(!augment(newconn)) return false;
			int n=match[base];
D(base);
			// if n!=-1 the augmenting path ended on this blossom

			if(n!=-1) REP(i, S) if(conn[blossom[i]][n]) {
				couple(blossom[i], n);
				if(i&1) for(int j=i+1; j<S; j+=2) couple(blossom[j],blossom[j+1]);
				else for(int j=0; j<i; j+=2) couple(blossom[j],blossom[j+1]);
				break;
			}
			return true;
		}
	}
	return false;
}

int edmonds(VVI &conn) {
	int res=0;
	match=VI(N,-1);
	while(augment(conn)) res++;
	return res;
}
int main()
{
	VVI g(10, VI(10, 0));
#define conn(x,y) g[x][y]=g[y][x] = 1;
	conn(1,2);
	conn(2,3);
	conn(2,5);
	conn(5,3);
	conn(3,4);
	conn(5,6);
	N = g.size();
	D(edmonds(g));
	return 0;
}

