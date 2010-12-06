bool Miller(LL p, LL s, int a){
    if(p==a) return 1;
    LL mod=expmod(a,s,p);
    for(;s-p+1 && mod-1 && mod-p+1;s*=2) mod=mulmod(mod,mod,p);
    return mod==p-1 || s%2;
}
bool isprime(LL n) {
    if(n<2)return 0; if(n%2==0) return n==2;
    LL s=n-1;
    while(s%2==0) s/=2;
    return Miller(n,s,2) && Miller(n,s,7) && Miller(n,s,61);
} // for 341*10^12  primes <= 17
