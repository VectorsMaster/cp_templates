#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define LL long long
#define pb push_back
#define F first
#define S second

const int KL=1e6;
using namespace std;

int n,m,q,nm;
string t,s;
vector <int> mx_pre;


void pre_compute(string v,int vsz){
    mx_pre.resize(vsz+2);
    mx_pre[0]=0;
    for(int i=1,k=0;i<vsz;i++){
        while(k>0 && v[i]!=v[k])k=mx_pre[k-1];
        if(v[i]==v[k]){mx_pre[i]=k+1;k++;}
        else mx_pre[i]=k;
    }
}

int KMP(string u,string v,int usz,int vsz){
    int ans=0;
    for(int i=0,k=0;i<usz;i++){
        while(k>0 && u[i]!=v[k])k=mx_pre[k-1];
        if(u[i]==v[k])k++;
        if(k==m){ans++;k=mx_pre[k-1];}
    }
    return ans;
}

int main(){
    cin>>q;
    while(q--){
        nm++;
        cin>>m>>s>>n>>t;
        printf("Test Case #%d\n",nm);
        pre_compute(s,m);
        printf("%d\n",KMP(t,s,n,m));
    }
    return 0;
}


//// Prefix function with preprocessing 


int prefix[KL],fback[KL][26];
void PF(){
    prefix[0]=0;
    for(int i=1,k=0;i<t.size();i++){
        while(k>0 && t[i]!=t[k])k=prefix[k-1];
        if(t[i]==t[k])prefix[i]=k+1,k++;
        else prefix[i]=k;
    }
    bool vis[(int)t.size()];
    memset(vis,0,sizeof vis);
    memset(fback,0,sizeof fback);
    for(int i=(int)t.size()-1;i>0;i--){
        if(vis[i])continue;

        int k=i;
        vector <int> vec;
        while(k>0){vec.pb(k);k=prefix[k-1];}
        vec.pb(k);
        reverse(all(vec));

        int mx[26];
        memset(mx,0,sizeof mx);
        for(auto v:vec){
            vis[v]=1;
            mx[t[v]-'a']=max(mx[t[v]-'a'],v);
            for(int j=0;j<26;j++)fback[v][j]=mx[j];
        }

    }
}

