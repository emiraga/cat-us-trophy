int bit[M],n;
void update(int x, int v) { while( x <= n ) { bit[x] += v; x += x & -x; } } 
int sum(int x) { int ret=0; while(x>0){ ret += bit[x]; x -= x & -x; } return ret; }
