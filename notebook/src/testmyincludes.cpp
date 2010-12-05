template<class T> inline T euclid(T a,T b,T &X,T &Y)
{
	if(a<0)	{ T d=euclid(-a,b,X,Y); X=-X; return d;	}
	if(b<0) { T d=euclid(a,-b,X,Y); Y=-Y; return d; }
	if(b==0) { X=1; Y=0; return a; }
	else{
		T d=euclid(b,a%b,X,Y);
		T t=X;
		X=Y;
		Y=t-(a/b)*Y;
		return d;
	}
}
bool isprime2(long long p, int iteration){
    if(p<2)
        return false;
    if(p!=2 && p%2==0)
        return false;
    long long s=p-1;
    while(s%2==0)
        s/=2;
    for(int i=0;i<iteration;i++){
        long long a=rand()%(p-1)+1,temp=s;
        long long mod=powermod(a,temp,p);
        while(temp!=p-1 && mod!=1 && mod!=p-1){
            mod=multiplymod(mod,mod,p);
            temp *= 2;
        }
        if(mod!=p-1 && temp%2==0)
            return false;
    }
    return true;
}
