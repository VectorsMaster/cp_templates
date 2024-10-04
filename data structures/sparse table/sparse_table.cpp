#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    // In this template the node contains minimum, maximum, first occurrences of minimum and maximum
    struct node {
        int mx,mn;
        node(): mx(0), mn(0) {}
        node(int _mn,int _mx,int pos){mn=_mn,mx=_mx;}
        node(node L,node R) {
            mn=min(L.mn,R.mn);
            mx=max(L.mx,R.mx);
        }
        void mrg(node L,node R) {
            mn=min(L.mn,R.mn);
            mx=max(L.mx,R.mx);
        }
    };
    vector<vector<node>> spt;
    vector<int> lg2;
    SparseTable(int MAX){spt=vector<vector<node>> (MAX,vector<node>(20));lg2=vector<int>(MAX+1,0);}
    void build(int n,vector<int> &vec) {
        for(int i=2;i<=n;i++)lg2[i]=lg2[i/2]+1;
        for(int i=0;i<n;i++)spt[i][0]=node(vec[i],vec[i],i);
        for(int j=1;(1<<j)<=n;j++) {
            for(int i=0;i+(1<<j)-1<n;i++) {
                spt[i][j].mrg(spt[i][j-1],spt[i+(1<<(j-1))][j-1]);
            }
        }
    }
    node query(int l,int r) {
        int len=lg2[r-l+1];
        return node(spt[l][len],spt[r-(1<<len)+1][len]);
    }
};