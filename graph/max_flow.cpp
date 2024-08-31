#include<bits/stdc++.h>
using namespace std;
const int KL=1e3+10;
#define LL long long
#define S second
#define F first

int n,m,pr[KL],a[KL],b[KL],c[KL],arr[KL];
vector <int> adj[KL];
LL cap[KL][KL],ans;

int bfs(int s,int t){
    memset(pr,-1,sizeof pr);
    queue<pair<int,LL>> q;
    pr[s]=-2;
    q.push({s,1e9});
    while(!q.empty()){
        int cur=q.front().F;
        LL flow=q.front().S;
        q.pop();
        for(auto v:adj[cur]){
            if(pr[v]==-1 && cap[cur][v]>0){
                pr[v]=cur;
                LL new_flow=min(flow,cap[cur][v]);
                if(v==t)return new_flow;
                q.push({v,new_flow});
            }
        }
    }
    return 0;
}

LL max_flow(int s,int t){
    LL flow=0;
    LL new_flow;
    new_flow=bfs(s,t);
    while(new_flow>0){
        flow+=new_flow;
        int cur=t;
        while(cur!=s){
            int prev=pr[cur];
            cap[prev][cur]-=new_flow;
            cap[cur][prev]+=new_flow;
            cur=prev;
        }
        new_flow=bfs(s,t);
    }
    return flow;
}