typedef pair<LL,LL> pii;
#define x first
#define y second

pii egcd( LL a, LL b ) {  // returns x,y | ax + by = gcd(a,b)
	if( b == 0 ) return pii( 1, 0 );
	else {
		pii d = egcd( b, a % b );
		return pii( d.y, d.x - d.y * ( a / b ) );
	}
}
