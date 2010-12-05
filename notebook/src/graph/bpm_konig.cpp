#define M 1010
int grid[M][M], l[M], r[M], seen[M], rows, cols;
bool dfs(int x)
{
    if( seen[x] ) return false;
    seen[x] = true;
    Rep(i,cols) if( grid[x][i] ) if( r[i] == -1 || dfs( r[i] ) )
    {
        r[i] = x, l[x] = i;
        return true;
    }
    return false;
}
int bpm() {
    SET( l, -1 );
    SET( r, -1 );
    int ret = 0;
    Rep(i,rows) {
        SET( seen, 0 ); 
        if( dfs( i ) ) ret ++;
    }   
    return ret;
}
bool lT[M], rT[M];
void konigdfs(int x)
{
    if( !lT[x] ) return; lT[x] = 0;
    Rep(i,cols) if(grid[x][i] && i != l[x])
    {
        rT[i] = true;
        if( r[i] != -1) konigdfs(r[i]);
    }
}
int konig()
{
    SET(lT, 1); SET(rT, 0);
    Rep(i,rows) if(l[i] == -1) konigdfs(i);
}
