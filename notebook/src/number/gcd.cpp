LL gcd( LL a, LL b ) { return !b ? a : gcd( b, a%b ); }
