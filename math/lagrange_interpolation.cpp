#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int KL=1e6+10;


const LL MOD=1e9+7;
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

// works only for points where x_i = i from 0 to y.size()-1
// values are integers 
// depends on the MOD and factorials (init() should be called before using this function)
int lagrange_interpolation(vector<int>& y,int x){
    int numerator=1,ret=0;
    for(int i=0;i<(int)y.size();i++){
        numerator=mul(numerator,sub(x,i));
    }
    for(int i=0;i<(int)y.size();i++){
        int L=inv[i];
        int R=((y.size()-1-i)%2==0?inv[(int)y.size()-1-i]:sub(0,inv[(int)y.size()-1-i]));
        int denominator_inv=mul(L,R); // inverse of denominator
        int numerator_i=mul(numerator,poow(sub(x,i),MOD-2));
        numerator_i=mul(denominator_inv,numerator_i);
        ret=add(ret,mul(y[i],numerator_i));
    }
    return ret;
}