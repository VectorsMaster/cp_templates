#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(),x.end()
#define LL long long
#define S second
#define F first
#define pb push_back

struct SuffixAutomation {
    struct state {
        int len=0,link=-1;
        map<char,int> next;
    };

    vector<state> st;
    vector<int> cnt;
    int sz,last;

    void init(int max_len) {
        st=vector<state>(2*max_len);
        cnt=vector<int>(2*max_len,0);
        st[0].len=0;
        st[0].link=-1;
        sz=1;
        last=0;
    }

    void extend(char c) {
        int cur=sz++;
        cnt[cur]=1;
        st[cur].len=st[last].len+1;
        int p=last;
        while(p!=-1 && !st[p].next.count(c)) st[p].next[c]=cur,p=st[p].link;
        if(p==-1) {st[cur].link=0,last=cur;return ;}
        int q=st[p].next[c];
        if(st[p].len+1==st[q].len) st[cur].link=q;
        else {
            int clone=sz++;
            st[clone].len=st[p].len+1;
            st[clone].next=st[q].next;
            st[clone].link=st[q].link;
            while(p!=-1 && st[p].next[c]==q) st[p].next[c]=clone,p=st[p].link;
            st[q].link=st[cur].link=clone;
        }
        last=cur;
    }

    void calc_cnt() {
        vector<int> sorted_states;
        for(int i=0;i<sz;i++)sorted_states.pb(i);
        sort(all(sorted_states),[&](int A,int B){return st[A].len>st[B].len;});
        for(auto s:sorted_states) {
            if(st[s].link!=-1)cnt[st[s].link]+=cnt[s];
        }
    }

    bool exists(string &p) {
        int cur=0;
        for(auto v:p) {
            if(!st[cur].next.count(v))return false;
            cur=st[cur].next[v];
        }
        return true;
    }

    // calc_cnt should be called before this function
    int count(string &p) {
        int cur=0;
        for(auto v:p) {
            if(!st[cur].next.count(v))return false;
            cur=st[cur].next[v];
        }
        return cnt[cur];
    }


    vector<LL> dp;
    LL count_substrings(int node) {
        if(dp[node]!=-1)return dp[node];
        LL ret=1;
        for(auto v:st[node].next) if(v.S<sz) ret+=count_substrings(v.S);
        return dp[node]=ret;
    }

    LL count_substrings() {
        dp=vector<LL>(sz,-1);
        return count_substrings(0);
    }
};