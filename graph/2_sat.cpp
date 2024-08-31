#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) x.begin(),x.end()
#define F first
#define S second

struct TwoSAT{
    // N is all Nodes of the two SAT including true and false.
    int N,NumberOfSCCs;
    vector<int> vout,vis,Scc;
    vector<pair<int,int>> edges;
    vector<vector<int>> E;
    void init(int _N){
        N=_N;
        vector<int> emp;
        vout.clear();
        vis.resize(N+1,0);
        E.resize(N+1,emp);
        Scc.resize(N+1,0);
        edges.clear();
    }
    int NOT(int val){return -val+N+1;}
    void add(int x,int y){edges.pb({x,y});}
    void ord(int node){
        vis[node]=1;
        for(auto v:E[node]){
            if(vis[v])continue;
            ord(v);
        }
        vout.pb(node);
    }
    void fndScc(int node){
        vis[node]=1;
        Scc[node]=NumberOfSCCs;
        for(auto v:E[node]){
            if(vis[v])continue;
            fndScc(v);
        }
    }
    void go(){
        for(int i=1;i<=N;i++)E[i].clear();
        for(int i=1;i<=N;i++)vis[i]=0;
        for(auto v:edges)E[v.F].pb(v.S);
        vout.clear();
        NumberOfSCCs=0;
        for(int i=1;i<=N;i++){
            if(!vis[i])ord(i);
        }
        for(int i=1;i<=N;i++)E[i].clear();
        for(auto v:edges)E[v.S].pb(v.F);
        reverse(all(vout));
        for(int i=1;i<=N;i++)vis[i]=0;
        for(auto v:vout){
            if(!vis[v]){
                NumberOfSCCs++;
                fndScc(v);
            }
        }
    }
    bool solve2SAT(){ // finds the true nodes
        for(int i=1;i<=N/2;i++){
            if(Scc[i]==Scc[NOT(i)]){return 0;}
        }
        return 1;
        //for(int i=1;i<=N/2;i++)if(Scc[i]>Scc[NOT(i)])Sol.pb(i);
    }
};
TwoSAT ST;