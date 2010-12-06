struct data {
	int nr[2],  p;
	bool operator<(const data &v)const{if(nr[0]==v.nr[0])return nr[1]<v.nr[1];return nr[0]<v.nr[0];}
	bool operator==(const data &v)const{return nr[1]==v.nr[1]&&nr[0]==v.nr[0];}
} L[MAXN];
int P[MAXLG+2][MAXN];
int suffix_array(char *A, int N)
{
	int step,cnt;
	REP(i,N) P[0][i] = A[i];
	for(step=1,cnt=1;cnt/2<N;cnt*=2,step++) {
		REP(i,N) L[i]=(data){P[step-1][i],(i+cnt<N)?P[step-1][i+cnt]:-1,i};
		sort(L,L+N);
		REP(i,N) P[step][L[i].p] = i && L[i]==L[i-1]? P[step][L[i-1].p]:i;
	}
	return step-1;
}
