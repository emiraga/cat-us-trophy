#define better(a,b) A[a]<A[b]?(a):(b)
int make_dp(int n) { // N log N
    REP(i,n) H[i][0]=i;
    for(int l=0,k; (k=1<<l) < n; l++) for(int i=0;i+k<n;i++)
        H[i][l+1] = better(H[i][l], H[i+k][l]);
}
int query_dp(int a, int b) {
	int l = __lg(b-a);
	return better(H[a][l], H[b-(1<<l)+1][l]);
}
