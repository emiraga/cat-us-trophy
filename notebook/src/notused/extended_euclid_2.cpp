// Finds g = gcd(a,b) and x, y such that ax+by=g. Bounds: |x|<=b+1, |y|<=a+1.
void gcdext(LL &g, LL &x, LL &y, LL a, LL b)
{ if (b == 0) { g = a; x = 1; y = 0; } else
{ gcdext(g, y, x, b, a % b); y = y - (a / b) * x; } }
LL modinv(LL a, LL N)
{
	LL x,y,g; gcdext(g,x,y, a,N );
	assert(g==1); return (x+N)%N;
}
