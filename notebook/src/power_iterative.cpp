LL power( LL a, LL b, LL mod ) {
    LL x = 1, y = a;
    while( b ) {
        if( b&1 ) x *= y, x %= mod;
        y *= y, y %= mod, b/=2;
    }
    return x%mod;
}
