VI e[M], c[M];
int n, d[M], p[M];
int inf = 1<<29;
int bford( int s, int f ) {
    REP(i,n) d[i] = i == s ? 0 : inf, p[i] = -1;
    REP(_,n-1) {
        bool done = 1;
        REP(i,n) REP(j,e[i].sz) {
            int u = i, v = e[i][j], uv = c[i][j];
            if( d[u] + uv < d[v] ) d[v] = d[u] + uv, p[v] = u, done = 0;
        }
        if( done ) break;
    }
    REP(i,n) REP(j,e[i].sz) {
        int u = i, v = e[i][j], uv = c[i][j];
        if( d[u] + uv < d[v] ) return -33;
    }
    if( d[f] == inf ) return -33; 
    return d[f];
}
