#include<bits/stdc++.h>
#define F first 
#define S second

using namespace std;

struct MaxSegTreeWithIndex{
    vector<pair<int,int>> seg;
    int N;
    MaxSegTreeWithIndex(){}
    MaxSegTreeWithIndex(int n) {
        seg=vector<pair<int,int>>(4*n+10);
        N=n;
    }

    void build(int cur,int st,int en,vector<int> &arr) {
        if(st==en){seg[cur]={arr[st],st};return;}
        int mid=(st+en)/2;
        build(2*cur,st,mid,arr);
        build(2*cur+1,mid+1,en,arr);
        seg[cur]=max(seg[2*cur],seg[2*cur+1]);
    }

    void update(int pos,int val,int cur,int st,int en) {
        if(st==en){seg[cur].F=val;return ;}
        int mid=(st+en)/2;
        if(pos<=mid)update(pos,val,2*cur,st,mid);
        else update(pos,val,2*cur+1,mid+1,en);
        seg[cur]=max(seg[2*cur],seg[2*cur+1]);
    }

    // becareful with return values for indecies out of the interval
    pair<int,int> query(int l,int r,int cur,int st,int en) {
        if(l>en || r<st)return {0,-1};
        if(l<=st && en<=r)return seg[cur];
        int mid=(st+en)/2;
        return max(query(l,r,2*cur,st,mid),query(l,r,2*cur+1,mid+1,en));
    }
};