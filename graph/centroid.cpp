#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define sc(x) scanf("%d",&x)
#define scl(x) scanf("%lld",&x)
#define LL long long
#define LD long double
#define pb push_back
#define F first
#define S second
const double PI=3.1415926535897932384626433;
const int KL=1e6+10;
const LL MOD=1e9+7;
using namespace std;

int n,m,ans,q,a[KL],x,y;
char str[KL];
string t;
vector <int> adj[KL];


// the start
bool deleted[KL]; // 1 deleted
int sz[KL],cnt[KL],k,Cen;
int dfs(int node,int pr){
    int ret=1;
    sz[node]=1;
    for(auto v:adj[node]){
        if(v==pr || deleted[v])continue;
        ret+=dfs(v,node);
        sz[node]+=sz[v];
    }
    return ret;
}
void calc(int node,int pr,int NumberOfNodes){
    bool ok=1;
    for(auto v:adj[node]){
        if(deleted[v])continue;
        if(v==pr){
            if(NumberOfNodes-sz[node]>NumberOfNodes/2)ok=0;
            continue;
        }
        calc(v,node,NumberOfNodes);
        if(sz[v]>NumberOfNodes/2)ok=0;
    }
    if(ok)Cen=node;
}
void precalc(int node,int pr,int len,int add){
    cnt[len]+=add;
    for(auto v:adj[node]){
        if(v==pr || deleted[v])continue;
        precalc(v,node,len+1,add);
    }
}
LL solve(int node,int pr,int len){
    if(len>k)return 0;
    LL ret=(LL)cnt[k-len];
    for(auto v:adj[node]){
        if(v==pr || deleted[v])continue;
        ret+= solve(v,node,len+1);
    }
    return ret;
}

LL Centroid_Decomposition(int root){
    int NumberOfNodes=dfs(root,root);
    Cen=-1;
    calc(root,root,NumberOfNodes);
    int Centroid=Cen;

    precalc(Centroid,Centroid,0,1);
    LL ret=(LL)cnt[k];
    for(auto v:adj[Centroid]){
        if(deleted[v])continue;
        precalc(v,Centroid,1,-1);
        ret+= solve(v,Centroid,1);
        precalc(v,Centroid,1,+1);
    }
    precalc(Centroid,Centroid,0,-1);
    ret/=2;
    
    deleted[Centroid]=1;
    for(auto v:adj[Centroid]){
        if(deleted[v])continue;
        ret+= Centroid_Decomposition(v);
    }
    deleted[Centroid]=0;
    return ret;
}








int main(){
    cin>>n>>k;
    for(int i=1;i<=n-1;i++){
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    cout<<Centroid_Decomposition(1)<<"\n";
    return 0;
}


//// Construct the centroid tree
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define sc(x) scanf("%d",&x)
#define scl(x) scanf("%lld",&x)
#define LL long long
#define LD long double
#define pb push_back
#define F first
#define S second
const double PI=3.1415926535897932384626433;
const int KL=1e6+10;
const LL MOD=1e9+7;
using namespace std;

int n,m,q,k,a[KL],x,y,ans[KL];
char str[KL];
string t;
vector <int> adj[KL];

/// start here
bool deleted[KL];
vector <int> e[KL],DisToPr[KL];
int p[KL],sz[KL];

int dfs(int node,int pr){
    int ret=1;
    sz[node]=1;
    for(auto v:adj[node]){
        if(v==pr || deleted[v])continue;
        ret+=dfs(v,node);
        sz[node]+=sz[v];
    }return ret;
}

int Find_Centroid(int node,int pr,int NumberOfNodes){
    int mx=-1,ok=1,child=0;
    for(auto v:adj[node]){
        if(deleted[v])continue;
        if(v==pr){
            if(NumberOfNodes-sz[node]>NumberOfNodes/2)ok=0;
            continue;
        }
        if(sz[v]>NumberOfNodes/2)ok=0;
        if(sz[v]>mx){mx=sz[v];child=v;}
    }
    if(ok)return node;
    return Find_Centroid(child,node,NumberOfNodes);
}
void solve(int node,int pr,int len){
    DisToPr[node].pb(len);
    for(auto v:adj[node]){
        if(v==pr || deleted[v])continue;
        solve(v,node,len+1);
    }
}

void Construct_Centroid_Tree(int root,int lst_centroid=-1){

    int NumberOfNodes=dfs(root,root);

    int Centroid=Find_Centroid(root,root,NumberOfNodes);

    p[Centroid]=lst_centroid;
    if(lst_centroid!=-1)e[lst_centroid].pb(Centroid);
    deleted[Centroid]=1;
    for(auto v:adj[Centroid]){
        if(deleted[v])continue;
        Construct_Centroid_Tree(v,Centroid);
    }
    deleted[Centroid]=0;
    solve(Centroid,Centroid,0);
}
void update(int pos){
    int node=pos,cnt=0;
    while(node!=-1){
        ans[node]=min(ans[node],DisToPr[pos][cnt]);
        cnt++;
        node=p[node];
    }
}
int query(int pos){
    int node=pos,cnt=0;
    int mn=1e9;
    while(node!=-1){
        mn=min(mn,ans[node]+DisToPr[pos][cnt]);
        cnt++;
        node=p[node];
    }
    return mn;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<n;i++){
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    Construct_Centroid_Tree(1);
    for(int i=1;i<=n;i++)ans[i]=1e9;
    update(1);
    while(m--){
        cin>>t>>x;
        if(t=="1")update(x);
        else {
            cout<<query(x)<<"\n";
        }
    }
    return 0;
}

