#include<bits/stdc++.h>
using namespace std;

struct Trie {
    struct node {
        node *ch[2];
        int freq;
        node(){ch[0]=ch[1]=nullptr,freq=0;}
    };
    node *root;
    const int sz=20;
    Trie() {root=nullptr;}

    void update(int val,int add) {
        if(!root)root=new node();
        node *cur=root;
        for(int i=sz-1;i>=0;i--) {
            int bt=((val>>i)&1);
            cur->freq+=add;
            if(!cur->ch[bt])cur->ch[bt]=new node();
            cur=cur->ch[bt];
        }
        cur->freq+=add;
    }
    int greater_or_equal(int val) {
        if(!root)return 0;
        node *cur=root;
        int ans=0;
        for(int i=sz-1;i>=0;i--) {
            int bt=((val>>i)&1);
            if(bt==0 && cur->ch[1]) ans+=cur->ch[1]->freq;
            if(!cur->ch[bt])return ans;
            cur=cur->ch[bt];
        }
        return ans+cur->freq;
    }
};

struct SegTrie {
    vector<Trie> seg;
    int MAX;
    SegTrie(int _max) {
        MAX=_max;
        seg=vector<Trie>(4*MAX+10);
    }
    void add(int i,int val,int cur,int st,int en) {
        seg[cur].update(val,1);
        if(st==en) return ;
        int mid=(st+en)/2;
        if(i<=mid)add(i,val,cur<<1,st,mid);
        else add(i,val,cur<<1|1,mid+1,en);
    }
    int greater_or_equal(int l,int r,int val,int cur,int st,int en) {
        if(l>en || r<st)return 0;
        if(l<=st && en<=r)return seg[cur].greater_or_equal(val);
        int mid=(st+en)/2;
        return greater_or_equal(l,r,val,cur<<1,st,mid)+greater_or_equal(l,r,val,cur<<1|1,mid+1,en);
    }

};