int H[100 * 1000 + 10][18];
void add(int x) { REP(i,18) H[x][i]++, x/=2; }
void del(int x) { REP(i,18) H[x][i]--, x/=2; }
int findkth(int k) {
	int a = 0, b = 17;
	while(b--) { a *= 2; if(H[a][b] < k) k-= H[a++][b]; }
	return a;
}
