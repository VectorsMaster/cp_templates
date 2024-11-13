#include<bits/stdc++.h>
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

using namespace std;



int mem[21][(1<<20)][2];
void FWHT_mod(vector<int>& Ha,vector<int>& a,int sz,bool inv){
    // Ha[i] = sum_[0<=j<2^sz]((-1)^(count(i&j))*a[j])
    // a[i] =
    for(int mask=0;mask<(1<<sz);mask++){
        int ret=a[mask];
        if(inv)ret=Ha[mask];
        mem[sz][mask][0]=ret;
        mem[sz][mask][1]=sub(0,ret); // -ret
    }
    for(int i=sz-1;i>=0;i--){
        for(int mask=0;mask<(1<<sz);mask++){
            for(int cnt=0;cnt<2;cnt++){
                if(!((1<<i)&mask))mem[i][mask][cnt]=add(mem[i+1][(mask|(1<<i))][cnt],mem[i+1][mask][cnt]);
                else mem[i][mask][cnt]=add(mem[i+1][mask][(cnt^1)],mem[i+1][(mask^(1<<i))][cnt]);
            }
        }
    }
    if(!inv){
        for(int j=0;j<(1<<sz);j++){
            Ha[j]=mem[0][j][0];
        }
    }
    else {
        int inv_2=poow((1<<sz),MOD-2);
        for(int j=0;j<(1<<sz);j++){
            a[j]=mul(mem[0][j][0],inv_2);
        }
    }
}

// this implementation can be optimized by making all vectors global instead of creating them inside the function
vector<int> xor_mul_mod(vector<int> &a,vector<int> &b,int sz){
    vector<int> Ha((1<<sz)),Hb((1<<sz)),c((1<<sz)),Hc((1<<sz));
    FWHT_mod(Ha,a,sz,false);
    FWHT_mod(Hb,b,sz,false);
    for(int i=0;i<(1<<sz);i++){
        Hc[i]=mul(Ha[i],Hb[i]);
    }
    FWHT_mod(Hc,c,sz,true);
    return c;
}
