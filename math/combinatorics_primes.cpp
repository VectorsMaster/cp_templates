#define LL long long
const int KL=1e6+10;

const LL MOD=998244353;
int mul(int x,int y){return x*1LL*y%MOD;}
int add(int x,int y){x+=y; if(x>=MOD)x-=MOD; return x;}
int sub(int x,int y){x-=y; if(x<0)x+=MOD; return x;}
int poow(int u,int v){
    if(v==0)return 1;
    int ret=poow(u,v/2);
    ret=mul(ret,ret);
    if(v%2==1)ret=mul(ret,u);
    return ret;
}
int fact[KL+10],invi[KL+10],inv[KL+10];
void init(){
    fact[0]=invi[0]=invi[1]=inv[0]=1;
    for(int i=1;i<KL;i++)fact[i]=mul(fact[i-1],i);
    for(int i=2;i<KL;i++)invi[i]=mul(invi[MOD%i],MOD-MOD/i);
    for(int i=1;i<KL;i++)inv[i]=mul(inv[i-1],invi[i]);
}
int C(int u,int v){
    if(u<v)return 0;
    return mul(fact[u],mul(inv[v],inv[u-v]));
}