template<class T> inline T euclid(T a,T b,T &X,T &Y)
{
    if(a<0) { T d=euclid(-a,b,X,Y); X=-X; return d; }
    if(b<0) { T d=euclid(a,-b,X,Y); Y=-Y; return d; }
    if(b==0) { X=1; Y=0; return a; }
    else { T d=euclid(b,a%b,X,Y); T t=X; X=Y; Y=t-(a/b)*Y; return d; }
}
int X[110],Y[110]; LL v[110];
void gen_euclid(int n)
{
    int g = a[0];
    FOR(i,1,n) g = euclid(g, a[i], X[i], Y[i]);
    LL mult = 1;
    FORD(i,n,1) v[i] = (mult * Y[i]) % m, mult = (mult * X[i]) % m;
    v[0] = mult;
}
