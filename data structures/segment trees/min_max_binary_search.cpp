#include<bits/stdc++.h>
using namespace std;

// make sure that min max boundaries are enough for problem statement
struct node{
    int mn,mx;
    node(){mn=1e9+1,mx=-1e9-1;}
    node(int _mn,int _mx){mn=_mn,mx=_mx;}
    node(node &A,node &B){
        mn=min(A.mn,B.mn);
        mx=max(A.mx,B.mx);
    }
    void mrg(node &A,node &B){
        mn=min(A.mn,B.mn);
        mx=max(A.mx,B.mx);
    }
};

// segment tree min-max and binary search on values
struct Stree{
    vector<node> seg;
    int N;

    void init(int _N){
        N=_N;
        seg.resize(4*_N+10);
    }

    void build(int cur,int st,int en,vector<int> &values){
        if(st==en){
            seg[cur]=node(values[st-1],values[st-1]);
            return ;
        }
        int mid=(st+en)/2;
        build(2*cur,st,mid,values);
        build(2*cur+1,mid+1,en,values);
        seg[cur].mrg(seg[2*cur],seg[2*cur+1]);
    }void build(vector<int> values){build(1,1,N,values);}

    void update(int pos,int val,int cur,int st,int en){
        if(st==en){seg[cur]=node(val,val);return ;}
        int mid=(st+en)/2;
        if(pos<=mid)update(pos,val,2*cur,st,mid);
        else update(pos,val,2*cur+1,mid+1,en);
        seg[cur].mrg(seg[2*cur],seg[2*cur+1]);
    }void update(int pos,int val){update(pos,val,1,1,N);}

    // First element larger or equal to val in range [l,r] inclusive
    int queryFL(int l,int r,int val,int cur,int st,int en){
        if(l>en || r<st || seg[cur].mx<val)return -1;
        if(st==en)return st;
        int mid=(st+en)/2;
        int ret=-1;
        if(seg[2*cur].mx>=val)ret=queryFL(l,r,val,2*cur,st,mid);
        if(ret!=-1)return ret;
        if(seg[2*cur+1].mx>=val)ret=queryFL(l,r,val,2*cur+1,mid+1,en);
        return ret;
    }int queryFL(int l,int r,int val){return queryFL(l,r,val,1,1,N);}

    // First element smaller or equal to val in range [l,r] inclusive
    int queryFS(int l,int r,int val,int cur,int st,int en){
        if(l>en || r<st || seg[cur].mn>val)return -1;
        if(st==en)return st;
        int mid=(st+en)/2;
        int ret=-1;
        if(seg[2*cur].mn<=val)ret=queryFS(l,r,val,2*cur,st,mid);
        if(ret!=-1)return ret;
        if(seg[2*cur+1].mn<=val)ret=queryFS(l,r,val,2*cur+1,mid+1,en);
        return ret;
    }int queryFS(int l,int r,int val){return queryFS(l,r,val,1,1,N);}

    // Last element smaller or equal val in range [l,r] inclusive
    int queryLS(int l,int r,int val,int cur,int st,int en){
        if(l>en || r<st || seg[cur].mn>val)return -1;
        if(st==en)return st;
        int mid=(st+en)/2;
        int ret=-1;
        if(seg[2*cur+1].mn<=val)ret=queryLS(l,r,val,2*cur+1,mid+1,en);
        if(ret!=-1)return ret;
        if(seg[2*cur].mn<=val)ret=queryLS(l,r,val,2*cur,st,mid);
        return ret;
    }int queryLS(int l,int r,int val){return queryLS(l,r,val,1,1,N);}

    // query min-max in range
    node query(int l,int r,int cur,int st,int en){
        if(l>en || r<st)return node();
        if(l<=st && en<=r)return seg[cur];
        int mid=(st+en)/2;
        node retL=query(l,r,2*cur,st,mid);
        node retR=query(l,r,2*cur+1,mid+1,en);
        return node(retL,retR);
    }node query(int l,int r){return query(l,r,1,1,N);}
};