#include <bits/stdc++.h>
#define LL long long
using namespace std;

struct SegTree {
    vector<LL> seg;
    vector<int> lzy;
    int MAX;

    SegTree(const int mx) {
        MAX=mx;
        seg.assign(4*MAX+10,0);
        lzy.assign(4*MAX+10,0);
    }

    void push_to_node(int add,int cur,int st,int en) {
        lzy[cur]+=add;
        seg[cur]+=(LL)add*(LL)(en-st+1);
    }

    void push(int cur,int st,int en) {
        if(!lzy[cur])return;
        int mid=((st+en)>>1);
        push_to_node(lzy[cur],cur<<1,st,mid);
        push_to_node(lzy[cur],cur<<1|1,mid+1,en);
        lzy[cur]=0;
    }

    void add_range(int l,int r,int add,int cur,int st,int en) {
        if(l>en || r<st)return ;
        if(l<=st && en<=r) {
            push_to_node(add,cur,st,en);
            return ;
        }
        push(cur,st,en);
        int mid=((st+en)>>1);
        add_range(l,r,add,cur<<1,st,mid);
        add_range(l,r,add,cur<<1|1,mid+1,en);
        seg[cur]=seg[cur<<1]+seg[cur<<1|1];
    }void add_range(int l,int r,int add){add_range(l,r,add,1,0,MAX);}

    int kth(int l,int r,int k,int cur,int st,int en) {
        if(r<st || l>en || k>seg[cur])return -1;
        if(st==en)return st;
        push(cur,st,en);
        int mid=((st+en)>>1);
        int ret=-1;
        if(seg[cur<<1]>=k)ret=kth(l,r,k,cur<<1,st,mid);
        if(ret!=-1)return ret;
        return kth(l,r,k-(int)seg[cur<<1],cur<<1|1,mid+1,en);
    }int kth(int l,int r,int k){return kth(l,r,k,1,0,MAX);}
};