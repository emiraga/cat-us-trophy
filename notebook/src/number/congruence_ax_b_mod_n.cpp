int congruence( int a, int b, int n ) { // finds ax = b(mod n) 
    int d = gcd( a, n );
    if( b % d != 0 ) return 1<<30; // no solution
    pii ans = egcd( a, n );
    int ret = ans.x * ( b/d + 0LL ), mul = n/d;
    ret %= mul;
    if( ret < 0 ) ret += mul;
    return ret;
}
