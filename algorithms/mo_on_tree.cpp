#include<bits/stdc++.h>
#include <stdio.h>
#include <algorithm>

#define all(x) x.begin(),x.end()
#define sc(x) scanf("%d",&x)
#define scl(x) scanf("%lld",&x)
#define LL long long
#define LD long double
#define pb push_back
#define F first
#define S second


const double PI=3.1415926535897932384626433;
const int KL=5e5+100;
const LL MOD=1e9+7;


using namespace std;

const int lg=19;
int n,m,q,c,up[KL][lg],x,y,in[KL],out[KL],timer,b[KL],a[KL],sq,l,r,ret[KL],ans,frnodes[KL],fr[2*KL],ord[KL];
vector <int> adj[KL];
pair< pair<int,int>, int >  qr[4*KL];
void dfs(int node=1,int pr=1,int cnt=0){
    up[node][0]=pr;
    for(int j=1;j<lg;j++)up[node][j]=up[up[node][j-1]][j-1];
    in[node]=timer++;
    for(auto v:adj[node]){
        if(v==pr)continue;
        dfs(v,node,cnt+1);
    }
    out[node]=timer++;
}
bool isan(int node1,int node2){
    return (in[node1]<=in[node2] && in[node2]<=out[node1]);
}
int _lca(int node1,int node2){
    if(isan(node1,node2))return node1;
    if(isan(node2,node1))return node2;
    for(int j=lg-1;j>=0;j--){
        if(!isan(up[node1][j],node2))node1=up[node1][j];
    }
    return up[node1][0];
}
bool cmp(int u,int v){
    if(qr[u].F.F/sq<qr[v].F.F/sq)return 1;
    if(qr[u].F.F/sq>qr[v].F.F/sq)return 0;
    return (qr[u].F.S<=qr[v].F.S);
}
void Change(int i){
    frnodes[a[i]]^=1;
    if(frnodes[a[i]]){
        ans+= (fr[b[a[i]]]==0);
        fr[b[a[i]]]++;
    }
    else {
        ans-= (fr[b[a[i]]]==1);
        fr[b[a[i]]]--;
    }
}
void update(int cur){
    while(r<=qr[cur].F.S)Change(r),r++;
    while(r>qr[cur].F.S+1)Change(r-1),r--;
    while(l<qr[cur].F.F)Change(l),l++;
    while(l>qr[cur].F.F)Change(l-1),l--;
}
void MO(){
    sq=sqrt(timer);
    for(int i=0;i<q;i++)ord[i]=i;
    sort(ord,ord+q,cmp);
    l=r=0;
    for(int j=0;j<q;j++){
        int i=ord[j];
        update(i);
        if(qr[i].S==-1){
            ret[i]=ans;
        }
        else {
            Change(qr[i].S);
            ret[i]=ans;
            Change(qr[i].S);
        }

    }
}


map <int,int> mp;
int main(){
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    while(cin>>n){
        mp.clear();
        int id=1;
        cin>>q;
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(!mp[b[i]]){
                mp[b[i]]=id;
                id++;
            }
            b[i]=mp[b[i]];
        }
        for(int i=1;i<=n-1;i++){
            cin>>x>>y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        dfs();
        for(int i=1;i<=n;i++)a[in[i]]=i,a[out[i]]=i;

        for(int i=0;i<q;i++){
            int u,v;
            cin>>u>>v;
            if(in[u]>in[v])swap(u,v);
            int P=_lca(u,v);
            if(P==u)qr[i]={{in[u],in[v]},-1};
            else qr[i]={{out[u],in[v]},in[P]};
        }
        //cout<<"START"<<endl;
        //for(int i=1;i<=n;i++)cout<<in[i]<<" "<<out[i]<<"\n";
        //for(int i=0;i<timer;i++)cout<<a[i]<<" ";cout<<endl;
        MO();
        for(int i=0;i<q;i++)cout<<ret[i]<<"\n";
    }




}
