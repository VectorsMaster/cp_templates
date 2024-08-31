int n,m,in[KL],out[KL],low[KL],timer,x,y;
vector <int> adj[KL];
bool vis[KL];
vector <pair<int,int>> bridges;
void dfs(int node,int pr=-1){
    vis[node]=1;
    in[node]=low[node]=++timer;
    for(auto v:adj[node]){
        if(v==pr)continue;
        if(vis[v]){
            low[node]=min(low[node],in[v]);
        }
        else {
            dfs(v,node);
            low[node]=min(low[node],low[v]);
            if(low[v]>in[node]){
                bridges.pb({node,v});
            }
        }
    }
}

set <int> cut;
void cutp(int node,int pr=-1){
    vis[node]=1;
    in[node]=low[node]=++timer;
    int children=0;
    for(auto v:adj[node]){
        if(v==pr)continue;
        if(vis[v])low[node]=min(low[node],in[v]);
        else {
            cutp(v,node);
            low[node]=min(low[node],low[v]);
            if(low[v]>=in[node] && pr!=-1)cut.insert(node);
            children++;
        }
    }
    if(children>1 && pr==-1)cut.insert(node);
}

/// Sccs

int n,m,x,y,cnt,sccpr[KL];
vector <int> adj[KL],edges[KL],scc[KL],vout;
bool vis[KL];
void ord(int node){
    vis[node]=1;
    for(auto v:edges[node]){
        if(vis[v])continue;
        ord(v);
    }
    vout.pb(node);
}
void fndscc(int node){
    vis[node]=1;
    scc[cnt].pb(node);
    sccpr[node]=cnt;
    for(auto v:adj[node]){
        if(vis[v])continue;
        fndscc(v);

    }
}
void go(){
    for(int i=1;i<=n;i++)if(!vis[i])ord(i);
    reverse(all(vout));
    memset(vis,0,sizeof vis);
    cnt=1;
    for(auto v:vout){
        if(!vis[v])fndscc(v),cnt++;
    }
}

