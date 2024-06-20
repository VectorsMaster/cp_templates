#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define S second
#define F first
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

// Works only for points where x_i = i from 0 to y.size()-1
// Values are integers 
// Depends on the MOD and factorials (init() should be called before using this function)
// x should be equal to any 0<=i<y.size() (otherwise, mod inverse will fail)
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

// The same rules as above 
// Handles the case when x can equal to some i (does not use mod inverse)
int lagrange_interpolation_pre_calc(vector<int>& y,int x){
    int numerator=1,ret=0;
    vector<int> prefix,suffix;
    for(int i=0;i<(int)y.size();i++){
        numerator=mul(numerator,sub(x,i));
        prefix.pb(numerator);
    }
    numerator=1;
    for(int i=(int)y.size()-1;i>=0;i--){
        numerator=mul(numerator,sub(x,i));
        suffix.pb(numerator);
    }reverse(all(suffix));

    for(int i=0;i<(int)y.size();i++){
        int L=inv[i];
        int R=((y.size()-1-i)%2==0?inv[(int)y.size()-1-i]:sub(0,inv[(int)y.size()-1-i]));
        int denominator_inv=mul(L,R); // inverse of denominator
        int numerator_i=mul((i==0?1:prefix[i-1]),(i==(int)y.size()-1?1:suffix[i+1]));
        numerator_i=mul(denominator_inv,numerator_i);
        ret=add(ret,mul(y[i],numerator_i));
    }
    return ret;
}

// It's not tested yet
// General function for lagrange interpolation
vector<int> lagrange_interpolation(vector<pair<LL,int>>& vec,vector<LL>& xs){
    vector<int> denominator((int)vec.size(),1);
    for(int i=0;i<(int)vec.size();i++){
        for(int j=0;j<(int)vec.size();j++){
            if(i==j)continue;
            denominator[i]=mul(denominator[i],sub(vec[i].F%MOD,vec[j].F%MOD));
        }
        denominator[i]=poow(denominator[i],MOD-2);
    }
    vector<int> ys;
    for(auto x:xs){
        int sum=0;
        for(int i=0;i<(int)vec.size();i++){
            int prod=denominator[i];
            for(int j=0;j<(int)vec.size();j++){
                if(j==i)continue;
                prod=mul(prod,sub(x%MOD,vec[j].F%MOD));
            }
            sum=add(sum,mul(vec[i].S,prod));
        }
        ys.pb(sum);
    }
    return ys;
}