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






struct Stree{
    int Sz;
    vector <int> seg;
    void init(int N){
        Sz=N;
        seg.resize(4*Sz+10);
    }

    int outside(){return -1e9;}
    int mrg(LL x,LL y){return max(x,y);}

    void build(int cur,int st,int en,vector <int> const& vec){
        if(st==en){
            seg[cur]=vec[st];
            return ;
        }
        int mid=(st+en)/2;
        build(2*cur,st,mid,vec);
        build(2*cur+1,mid+1,en,vec);
        seg[cur]=mrg(seg[2*cur],seg[2*cur+1]);
    }void build(vector <int> const& vec){build(1,0,Sz,vec);}


    void update(int pos,int val,int cur,int st,int en){
        if(st==en){
            seg[cur]=val;
            return ;
        }
        int mid=(st+en)/2;
        if(pos<=mid)update(pos,val,2*cur,st,mid);
        else update(pos,val,2*cur+1,mid+1,en);
        seg[cur]=mrg(seg[2*cur],seg[2*cur+1]);
    }void update(int pos,int val){update(pos,val,1,0,Sz);}

    int query(int l,int r,int cur,int st,int en){
        if(l>en || r<st)return outside();
        if(l<=st && en<=r)return seg[cur];
        int mid=(st+en)/2;
        return mrg(query(l,r,2*cur,st,mid),query(l,r,2*cur+1,mid+1,en));
    }int query(int l,int r){return query(l,r,1,0,Sz);}
};




int n,head[KL],heavy[KL],sz[KL],p[KL],depth[KL],pos[KL],val[KL];
vector <pair<int,int>> adj[KL];

void calc(int node,int pr){
    if(node==pr)depth[node]=0;
    p[node]=pr;
    int mx=-1;
    for(auto u:adj[node]){
        int v=u.F;
        if(v==pr)continue;
        depth[v]=depth[node]+1;
        calc(v,node);
        ///val[v]=u.S; only for edges queries
        sz[node]+=sz[v];
        if(sz[v]>mx){heavy[node]=v;mx=sz[v];}
    }
    if(mx==-1)heavy[node]=-1;
}
void Decompose(int node,int h){
    head[node]=h;
    if(heavy[node]!=-1){
        Decompose(heavy[node],h);
    }
    for(auto u:adj[node]){
        int v=u.F;
        if(v==p[node] || v==heavy[node])continue;
        Decompose(v,v);
    }
}
vector <Stree> T;
void DS(vector <int> const& vec){
    Stree cur;
    cur.init((int)vec.size()-1);
    cur.build(vec);
    T.pb(cur);
}
vector <int> GetNodes(int node,int anc){
    vector <int> Path;
    while(node!=anc){
        pos[node]=(int)T.size();
        Path.pb(val[node]);
        node=p[node];
    }
    pos[anc]=(int)T.size();
    Path.pb(val[anc]);
    reverse(all(Path));
    return Path;
}
void init(){
    calc(1,1);
    Decompose(1,1);
    for(int i=2;i<=n;i++){
        if((int)adj[i].size()>1)continue;
        vector <int> vec=GetNodes(i,head[i]);
        DS(vec);
    }
}

void update_node(int n1,int _val){
    val[n1]=_val;
    T[pos[n1]].update(depth[n1]-depth[head[n1]],val[n1]);
}

int path_of_nodes_query(int n1,int n2){
    int ret=-1e9;
    for(;head[n1]!=head[n2];n2=p[head[n2]]){
        if(depth[head[n1]]>depth[head[n2]])swap(n1,n2);
        ret=max(ret,T[pos[n2]].query(0,depth[n2]-depth[head[n2]]));
    }
    if(depth[n1]>depth[n2])swap(n1,n2);
    ret=max(ret,T[pos[n2]].query(depth[n1]-depth[head[n1]],depth[n2]-depth[head[n2]]));
    return ret;
}


int q,x,y,z;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>val[i];
    for(int i=1;i<n;i++){
        cin>>x>>y;
        adj[x].pb({y,0});
        adj[y].pb({x,0});
    }
    init();

    while(q--){
        int t;
        cin>>t;
        if(t==1){
            cin>>x>>y;
            update_node(x,y);
        }
        else {
            cin>>x>>y;
            cout<<path_of_nodes_query(y,x)<<" ";
        }
    }cout<<"\n";
    return 0;
}
