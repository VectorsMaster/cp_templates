#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int KL=1e6+10;
int a[KL],n;
vector<int> v;
void compress(){
	v.clear() ;
	for(int i=1;i<=n;++i)v.push_back(a[i]);
	sort(v.begin() , v.end()) ;
	v.erase(unique(v.begin() , v.end()) , v.end()) ;
	for(int i=1;i<=n;++i){
        a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin();
		a[i]++;
	}
}

int lstGr[KL],nxtGr[KL],lstSm[KL],nxtSm[KL];
void prep(){
    // Last and next element greater or equal, Last and next element smaller or equal
    vector <int> vec;
    a[0]=1e9+1;
    a[n+1]=1e9+1;
    vec.pb(0);
    for(int i=1;i<=n;i++){
        while(a[vec.back()]<a[i])vec.pop_back();
        lstGr[i]=vec.back();
        vec.pb(i);
    }
    vec.clear();
    vec.pb(n+1);
    for(int i=n;i>=1;i--){
        while(a[vec.back()]<a[i])vec.pop_back();
        nxtGr[i]=vec.back();
        vec.pb(i);
    }
    vec.clear();
    a[0]=-1;
    a[n+1]=-1;
    vec.pb(0);
    for(int i=1;i<=n;i++){
        while(a[vec.back()]>a[i])vec.pop_back();
        lstSm[i]=vec.back();
        vec.pb(i);
    }
    vec.clear();
    vec.pb(n+1);
    for(int i=n;i>=1;i--){
        while(a[vec.back()]>a[i])vec.pop_back();
        nxtSm[i]=vec.back();
        vec.pb(i);
    }
}