#include<bits/stdc++.h>
#define LL long long
using namespace std;

struct SegTreeSum {
    vector<LL> seg;
    int MAX;

    SegTreeSum(const int mx) {
        MAX=mx;
        seg.assign(4*MAX+10,0);
    }

    void add_val(int pos,int add,int cur,int st,int en) {
        if(st==en) {
            seg[cur]+=add;
            return ;
        }
        int mid=((st+en)>>1);
        if(pos<=mid)add_val(pos,add,cur<<1,st,mid);
        else add_val(pos,add,cur<<1|1,mid+1,en);
        seg[cur]=seg[cur<<1]+seg[cur<<1|1];
    }void add_val(int pos,int add){add_val(pos,add,1,0,MAX);}

    int query(int l,int r,int cur,int st,int en) {
        if(l>en || r<st)return 0;
        if(l<=st && en<=r)return seg[cur];
        int mid=((st+en)>>1);
        return query(l,r,cur<<1,st,mid)+query(l,r,cur<<1|1,mid+1,en);
    }int query(int l,int r){return query(l,r,1,0,MAX);}

    int kth(int l,int r,int k,int cur,int st,int en) {
        if(r<st || l>en || k>seg[cur])return -1;
        if(st==en)return st;
        int mid=((st+en)>>1);
        int ret=-1;
        if(seg[cur<<1]>=k)ret=kth(l,r,k,cur<<1,st,mid);
        if(ret!=-1)return ret;
        return kth(l,r,k-(int)seg[cur<<1],cur<<1|1,mid+1,en);
    }int kth(int l,int r,int k){return kth(l,r,k,1,0,MAX);}
};