#include<bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> seg;
    vector<int> lzy;
    int MAX;

    SegTree(const int mx,int is_prefix) {
        MAX=mx;
        seg.assign(4*MAX+10,0);
        lzy.assign(4*MAX+10,0);
    }

    void push_to_node(int add,int cur,int st,int en) {
        lzy[cur]+=add;
        seg[cur]+=add;
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
        seg[cur]=max(seg[cur<<1],seg[cur<<1|1]);
    }void add_range(int l,int r,int add){add_range(l,r,add,1,0,MAX);}

    int query(int l,int r,int cur,int st,int en){
        if(l>en || r<st)return -1e9;
        if(l<=st && en<=r)return seg[cur];
        push(cur,st,en);
        int mid=(st+en)>>1;
        return max(query(l,r,cur<<1,st,mid),query(l,r,cur<<1|1,mid+1,en));
    }int query(int l,int r){return query(l,r,1,0,MAX);}

    int get(int pos,int cur,int st,int en){
        if(st==en)return seg[cur];
        push(cur,st,en);
        int mid=(st+en)>>1;
        if(pos<=mid)return get(pos,cur<<1,st,mid);
        return get(pos,cur<<1|1,mid+1,en);
    }int get(int pos){return get(pos,1,0,MAX);}
};
