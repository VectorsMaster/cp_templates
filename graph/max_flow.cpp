#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj,cap;
vector<int> pr;

int max_flow(int s,int t,int TOT){ // be careful with flow data type (LL or int)
    auto bfs=[&](){
        for(int i=0;i<TOT;i++)pr[i]=(i==s?-2:-1);
        queue<pair<int,int>> q; q.push({s,1e9});
        while(!q.empty()){
            auto [cur,flow]=q.front();q.pop();
            for(auto v:adj[cur]){
                if(pr[v]!=-1 || cap[cur][v]==0)continue;
                pr[v]=cur;
                int new_flow=min(flow,cap[cur][v]);
                if(v==t)return new_flow;
                q.push({v,new_flow});
            }
        }return 0;
    };
    int flow=0;
    while(int new_flow=bfs()>0){
        flow+=new_flow;
        for(int cur=t;cur!=s;cur=pr[cur])
            cap[pr[cur]][cur]-=new_flow,cap[cur][pr[cur]]+=new_flow;
    }
    return flow;
}