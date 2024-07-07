#define LL long long

// sum[0<=i<=n] floor((ai+b)/c)
// a,b,c,n>=0
LL floor_sum(LL a,LL b,LL c,LL n){
    LL ret=0;
    if(a==0){
        return (n+1)*(b/c);
    }
    if(a>=c || b>=c){
        // a = qc + a_prime
        ret+=a/c*n*(n+1LL)/2;
        ret+=b/c*(n+1LL);
        return ret+floor_sum(a%c,b%c,c,n);
    }
    // ans = sum[1<=j<=floor((an+b)/c)] (n-ceil((jc-b)/a)+1)
    // ans = sum[1<=j<=floor((an+b)/c)] (n-floor((jc-b+a-1)/a+1)
    // ans = sum[0<=j<floor((an+b)/c)] (n-floor((jc+c-b-1)/a))
    LL new_n=(a*n+b)/c-1;
    ret=(new_n+1LL)*n;
    ret-=floor_sum(c,c-1-b,a,new_n);
    return ret;
}