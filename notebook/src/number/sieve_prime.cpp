const int MAX = 100000000;
int p[ MAX/64 + 2 ];
int np = 0;
#define on(x) ( p[x/64] & (1<<( (x%64)/2 ) ) )
#define turn(x)  p[x/64] |= (1<<( (x%64)/2 ) )
void sieve() {
	for(int i=3;i*i<MAX; i+=2) 	{
		if( !on(i) ) {
			int ii = i*i;
			int i2 = i+i;
			for(int j=ii; j<MAX; j+=i2) turn(j);
		}
	}
}
inline bool prime( int num ) {
	return num > 1 && ( num == 2 || ( (num&1) && !on( num ) ) ); 
}
