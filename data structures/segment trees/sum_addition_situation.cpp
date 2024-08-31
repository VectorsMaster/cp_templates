#include<bits/stdc++.h>
using namespace std;
#define LL long long

struct Stree{
    /// addition on ranges and index (operations affects only available positions)
    /// operation of changing the situation is valid only on specific position
    int Sz;
    vector <LL> lzy,valid,sum;
    void init(int N){
        Sz=N;
        lzy.resize(4*N+10,0);
        valid.resize(4*N+10,0);
        sum.resize(4*N+10,0);
    }
    void _Push(int cur,int st,int en){
        if(lzy[cur]==0)return ;
        lzy[2*cur]+=lzy[cur];
        lzy[2*cur+1]+=lzy[cur];
        sum[2*cur]+= lzy[cur]*valid[2*cur];
        sum[2*cur+1]+= lzy[cur]*valid[2*cur+1];
        lzy[cur]=0;
    }
    void add(int l,int r,LL val,int cur,int st,int en){
        if(l>en || r<st)return ;
        if(l<=st && en<=r){
            lzy[cur]+= val;
            sum[cur]+= val * valid[cur];
            return ;
        }
        _Push(cur,st,en);
        int mid=(st+en)/2;
        add(l,r,val,2*cur,st,mid);
        add(l,r,val,2*cur+1,mid+1,en);
        sum[cur]=sum[2*cur]+sum[2*cur+1];
    }void add(int l,int r,LL val){add(l,r,val,1,1,Sz);}

    void _Switch(int pos,LL val,int sit,int cur,int st,int en){
        if(st==en){
            lzy[cur]=0;
            valid[cur]=sit;
            sum[cur]=val;
            return ;
        }
        _Push(cur,st,en);
        int mid=(st+en)/2;
        if(pos<=mid)_Switch(pos,val,sit,2*cur,st,mid);
        else _Switch(pos,val,sit,2*cur+1,mid+1,en);
        sum[cur]=sum[2*cur]+sum[2*cur+1];
        valid[cur]=valid[2*cur]+valid[2*cur+1];
    }void Switch(int pos,LL val,int sit){_Switch(pos,val,sit,1,1,Sz);}

    LL query(int l,int r,int cur,int st,int en){
        if(l>en || r<st)return 0LL;
        if(l<=st && en<=r)return sum[cur];
        _Push(cur,st,en);
        int mid=(st+en)/2;
        return query(l,r,2*cur,st,mid)+query(l,r,2*cur+1,mid+1,en);
    }LL query(int l,int r){return query(l,r,1,1,Sz);}


    LL Count(int l,int r,int cur,int st,int en){
        if(l>en || r<st)return 0LL;
        if(l<=st && en<=r)return valid[cur];
        _Push(cur,st,en);
        int mid=(st+en)/2;
        return Count(l,r,2*cur,st,mid)+Count(l,r,2*cur+1,mid+1,en);
    }LL Count(int l,int r){return Count(l,r,1,1,Sz);}
};