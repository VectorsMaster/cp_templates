#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;


struct hashing {
    const int sz=4;
    const LL MOD[4]={1000000007,1000000009,900004151,900000947};
    const int primes[4]={500069,500953,501451,502651};
    vector<int> inv;
    vector<vector<int>> pw;


    hashing() {}

    hashing(int N) { // N is the maximum size of the object to be hashed.
        inv=vector<int>(sz,0);
        pw=vector<vector<int>>(sz,vector<int>(N+1,1));
        for(int j=0;j<sz;j++) {
            inv[j]=power(primes[j],MOD[j]-2,j);
            for(int i=1;i<=N;i++)
                pw[j][i]=mul(pw[j][i-1],primes[j],j);
        }
    }

    int mul(int x,int y,int j){return x*1LL*y%MOD[j];}
    int add(int x,int y,int j){x+=y; if(x>=MOD[j])x-=MOD[j]; return x;}
    int sub(int x,int y,int j){x-=y; if(x<0)x+=MOD[j]; return x;}
    int power(int u,int v,int j){
        if(v==0)return 1;
        int ret=power(u,v/2,j);
        ret=mul(ret,ret,j);
        if(v%2==1)ret=mul(ret,u,j);
        return ret;
    }

    vector<int> hash(deque<int> &deq) {
        vector<int> sum(sz,0);
        int id=0;
        for(auto v:deq) {
            for(int j=0;j<4;j++)sum[j]=add(sum[j],mul(pw[j][id],v,j),j);
            id++;
        }
        return sum;
    }

    void cycle_hash_left(deque<int> &deq,vector<int> &cur) {
        for(int j=0;j<4;j++) {
            cur[j]=sub(cur[j],deq.front(),j);
            cur[j]=mul(cur[j],inv[j],j);
        }
        deq.pb(deq.front());
        deq.pop_front();
        for(int j=0;j<4;j++)
            cur[j]=add(cur[j],mul(pw[j][(int)deq.size()-1],deq.back(),j),j);
    }


    // this procedure was not test yet
    void cycle_hash_right(deque<int> &deq,vector<int> &cur) {
        for(int j=0;j<4;j++) {
            cur[j]=sub(cur[j],mul(deq.back(),pw[j][(int)deq.size()-1],j),j);
            cur[j]=mul(cur[j],primes[j],j);
        }
        deq.push_front(deq.back());
        deq.pop_back();
        for(int j=0;j<4;j++)
            cur[j]=add(cur[j],deq.front(),j);
    }

};
