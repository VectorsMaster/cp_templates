#include<bits/stdc++.h>
#define S second
#define F first
#define all(x) x.begin(),x.end()
using namespace std;    
int main(){
    string t;cin>>t;
    t+='$';
    int n=t.size();
    vector <int> p(n),c(n);

    vector <pair<char,int>> a(n);
    for(int i=0;i<n;i++)a[i]={t[i],i};
    sort(all(a));

    for(int i=0;i<n;i++)p[i]=a[i].S;
    c[p[0]]=0;
    for(int i=1;i<n;i++)
    {
        if(a[i].F==a[i-1].F)c[p[i]]=c[p[i-1]];
        else c[p[i]]=c[p[i-1]]+1;
    }

    ///for(int i=0;i<n;i++)cout<<p[i]<<" "<<t.substr(p[i],n)<<endl;cout<<endl;

    int k=0;
    while((1<<k)<n)
    {
        vector <pair<pair<int,int>,int>> a(n);
        for(int i=0;i<n;i++)a[i]={{c[i],c[(i+(1<<k))%n]},i};
        sort(all(a));
        for(int i=0;i<n;i++)p[i]=a[i].S;
        c[p[0]]=0;
        for(int i=1;i<n;i++)
        {
            if(a[i].F==a[i-1].F)c[p[i]]=c[p[i-1]];
            else c[p[i]]=c[p[i-1]]+1;
        }

        ///for(int i=0;i<n;i++)cout<<p[i]<<" "<<t.substr(p[i],n)<<endl;cout<<endl;

        k++;
    }
    for(int i=0;i<n;i++)cout<<p[i]<<" ";
}