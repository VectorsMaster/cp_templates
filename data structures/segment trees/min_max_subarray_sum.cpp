#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int KL=1e6+10;

struct max_node{
    LL sum,pref,suff,opt;
    max_node(){
        sum=0;
        pref=0;
        suff=0;
        opt=0;
    }
    max_node(LL val){
        sum=val;
        pref=val;
        suff=val;
        opt=val;
    }
    max_node(LL _sum,LL _pref,LL _suff,LL _opt){
        sum=_sum;
        pref=_pref;
        suff=_suff;
        opt=_opt;
    }
    max_node(max_node a,max_node b){
        sum=a.sum+b.sum;
        pref=max(a.sum+b.pref,a.pref);
        suff=max(b.suff,b.sum+a.suff);
        opt=max(a.opt,b.opt);
        opt=max(opt,a.suff+b.pref);
    }
};

struct min_node{
    LL sum,pref,suff,opt;
    min_node(){
        sum=0;
        pref=0;
        suff=0;
        opt=0;
    }
    min_node(LL val){
        sum=val;
        pref=val;
        suff=val;
        opt=val;
    }
    min_node(LL _sum,LL _pref,LL _suff,LL _opt){
        sum=_sum;
        pref=_pref;
        suff=_suff;
        opt=_opt;
    }
    min_node(min_node a,min_node b){
        sum=a.sum+b.sum;
        pref=min(a.sum+b.pref,a.pref);
        suff=min(b.suff,b.sum+a.suff);
        opt=min(a.opt,b.opt);
        opt=min(opt,a.suff+b.pref);
    }
};

struct node{
    min_node mn;
    max_node mx;
    node(){

    }
    node(min_node mn_node,max_node mx_node){
        mn=mn_node;
        mx=mx_node;
    }
    node(node a,node b){
        mn=min_node(a.mn,b.mn);
        mx=max_node(a.mx,b.mx);
    }
};





LL n,a[KL];
const LL INF=(LL)1e17;
struct Tree{
    vector<node> seg;
    int N;

    Tree(){
        seg.clear();
        N=0;
    }
    void init(int n){
        seg.resize(4*n+1);
        N=n;
    }

    void build(int cur,int st,int en,vector<node>& vec){
        if(st==en){
            seg[cur]=vec[st];
            return ;
        }
        int mid=(st+en)/2;
        build(2*cur,st,mid,vec);
        build(2*cur+1,mid+1,en,vec);
        seg[cur]=node(seg[2*cur],seg[2*cur+1]);
    }

    node query(int l,int r,int cur,int st,int en){
        if(l>en || r<st || l>r){
            min_node mn_node=min_node(0,INF,INF,INF);
            max_node mx_node=max_node(0,-INF,-INF,-INF);
            return node(mn_node,mx_node);
        }

        if(l<=st && en<=r)return seg[cur];
        int mid=(st+en)/2;
        return node(query(l,r,2*cur,st,mid),query(l,r,2*cur+1,mid+1,en));
    }

    max_node get(int l,int r,int cur,int st,int en){
        if(l>en || r<st || l>r)return max_node(0,-INF,-INF,-INF);
        if(l<=st && en<=r)return seg[cur].mx;
        int mid=(st+en)/2;
        return max_node(get(l,r,2*cur,st,mid),get(l,r,2*cur+1,mid+1,en));

    }

};