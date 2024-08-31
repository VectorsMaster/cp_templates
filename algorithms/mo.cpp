#include<bits/stdc++.h>
#include <stdio.h>
#include <algorithm>

#define all(x) x.begin(),x.end()
#define sc(x) scanf("%d",&x)
#define scl(x) scanf("%lld",&x)
#define LL long long
#define LD long double
#define pb push_back
#define F first
#define S second


const double PI=3.1415926535897932384626433;
const int KL=1e6+5;
const LL MOD=1e9+7;


using namespace std;

int n,a[30005],q,qs[(int)2e5+5],qe[(int)2e5+5],e,s,qi[(int)2e5+5];
int qa[(int)2e5+5];
int freq[KL],cnt;

void add(int val){cnt+=!freq[val]++;}
void rem(int val){cnt-=!--freq[val];}

void update(int cur){
    while(e<=qe[cur])add(a[e++]);
    while(s>qs[cur])add(a[--s]);
    while(e>qe[cur]+1)rem(a[--e]);
    while(s<qs[cur])rem(a[s++]);
}

void mo(){
    int sq=(int)sqrt(n);
    sort(qi,qi+q,[sq](int a,int b){return make_pair(qs[a]/sq,qe[a])<make_pair(qs[b]/sq,qe[b]);});
    s=e=0;
    for(int i=0;i<q;i++){
        int cur=qi[i];
        update(cur);
        qa[cur]=cnt;
    }
}
int main()
{
    sc(n);
    for(int i=0;i<n;i++)sc(a[i]);
    sc(q);
    for(int i=0;i<q;i++){
        qi[i]=i;
        sc(qs[i]);sc(qe[i]);
        qs[i]--;
        qe[i]--;
    }
    mo();
    for(int i=0;i<q;i++){
        printf("%d\n",qa[i]);
    }

    return 0;
}
