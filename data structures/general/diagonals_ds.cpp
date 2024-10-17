#include<bits/stdc++.h>
using namespace std;

#define pb push_back
struct SparseTable {
    vector<vector<int>> spt;
    vector<int> lg2;
    SparseTable(){}
    SparseTable(int MAX,int _lg){spt=vector<vector<int>> (MAX,vector<int>(_lg));lg2=vector<int>(MAX+1,0);}

    void build(int n,vector<int> &vec) {
        for(int i=2;i<=n;i++)lg2[i]=lg2[i/2]+1;
        for(int i=0;i<n;i++)spt[i][0]=vec[i];
        for(int j=1;(1<<j)<=n;j++) {
            for(int i=0;i+(1<<j)-1<n;i++) {
                spt[i][j]=max(spt[i][j-1],spt[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l,int r) {
        if(l>r)return 0;
        int len=lg2[r-l+1];
        return max(spt[l][len],spt[r-(1<<len)+1][len]);
    }
};


struct diagonals_DS {
    int n,m;
    vector<SparseTable> spt_sum,spt_sub;
    vector<vector<int>> sum,sub;
    diagonals_DS(){n=0,m=0;}
    diagonals_DS(vector<vector<int>> &matrix) {
        n=matrix.size();
        m=matrix[0].size();
        sum=vector<vector<int>>(n+m-1,vector<int>());
        sub=vector<vector<int>>(n+m-1,vector<int>());
        spt_sum=vector<SparseTable>(n+m-1);
        spt_sub=vector<SparseTable>(n+m-1);
        // sum [0,n-1+m-1]
        // sub [-(m-1),n-1]
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                sum[i+j].pb(matrix[i][j]);
                sub[i-j+(m-1)].pb(matrix[i][j]);
            }
        }
        for(int i=0;i<n+m-1;i++) {
            spt_sum[i]=SparseTable(sum[i].size(),15);
            spt_sum[i].build((int)sum[i].size(),sum[i]);
            spt_sub[i]=SparseTable(sub[i].size(),15);
            spt_sub[i].build((int)sub[i].size(),sub[i]);
        }
    }
    pair<int,int> endpoints_sum(int val,int id) {
        assert(id<(int)sum[val].size());
        // x + y = val
        int x=(val<=m-1?0:val-(m-1)),y=val-x;
        return {x+id,y-id};
    }
    pair<int,int> endpoints_sub(int val,int id) {
        assert(id<(int)sub[(m-1)+val].size());
        // x - y = val
        int x=(val<=0?0:val),y=x-val;
        return {x+id,y+id};
    }

    int query_sum_diagonal(int val,int i,int j) {// points which have same distance from (i,j)
        int idl=0,idr=(int)sum[val].size()-1;
        auto [l_start,r_start]=endpoints_sum(val,idl);
        auto [l_end,r_end]=endpoints_sum(val,idr);
        if(val>=i+j) {
            if(l_start<i)idl+=i-l_start;
            if(r_end<j)idr-=j-r_end;
        }
        else {
            if(r_start>j)idl+=r_start-j;
            if(l_end>i)idr-=l_end-i;
        }
        return spt_sum[val].query(idl,idr);
    }

    int query_sub_diagonal(int val,int i,int j) {
        int idl=0,idr=(int)sub[(m-1)+val].size()-1;
        auto [l_start,r_start]=endpoints_sub(val,idl);
        auto [l_end,r_end]=endpoints_sub(val,idr);
        if(val>=i-j) {
            if(l_start<i)idl+=i-l_start;
            if(r_end>j)idr-=r_end-j;
        }
        else {
            if(r_start<j)idl+=j-r_start;
            if(l_end>i)idr-=l_end-i;
        }
        return spt_sub[(m-1)+val].query(idl,idr);
    }

    int query_equal_dis(int x,int y,int i) {// query all points with distance i from (x,y)
        int ret=-1e9;
        // sum diagonals
        if(x+y-i>=0)ret=max(ret,query_sum_diagonal(x+y-i,x,y));
        if(x+y+i<n+m-1)ret=max(ret,query_sum_diagonal(x+y+i,x,y));

        // sub diagonals
        if(x-y-i>=-(m-1))ret=max(ret,query_sub_diagonal(x-y-i,x,y));
        if(x-y+i<=(n-1))ret=max(ret,query_sub_diagonal(x-y+i,x,y));
        return ret;
    }
};