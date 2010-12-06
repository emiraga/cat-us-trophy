#define M 100
int grid[M][M];
int l[M], r[M], seen[M];
int rows, cols;
bool dfs(int x) {
    if( seen[x] ) return 0;
    seen[x] = true;
    REP(i,cols) if( grid[x][i] ) {
        if( r[i] == -1 || dfs( r[i] ) ) {
            r[i] = x, l[x] = i;
            return true;
        }
    }
    return false;
}
int bpm() {
    SET( l, -1 );
    SET( r, -1 );
    int ret = 0;
    REP(i,rows) {
        SET( seen, 0 ); 
        if( dfs( i ) ) ret ++;
    }   
    return ret;
}
