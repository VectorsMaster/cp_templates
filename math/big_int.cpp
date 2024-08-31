#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define LL long long

#define pb push_back
#define F first
#define S second
const int KL=1e6+10;
const LL inf=(LL)100000000000000000000;
using namespace std;

LL p,q;
vector<int> P,Q;

vector<int> conv(LL x){
    vector<int> ret;
    while(x>0){
        LL md=x%10LL;
        ret.pb(md);
        x/=10LL;
    }
    return ret;
}
void print(vector<int> vec){
    for(int j=vec.size()-1;j>=0;j--){
        cout<<vec[j];
    }cout<<"\n";
}

vector<int> add(vector<int> vec1,vector<int> vec2){
    if(vec1.size()<vec2.size())swap(vec1,vec2);
    vec1.pb(0);
    while(vec2.size()<vec1.size()){
        vec2.pb(0);
    }
    for(int j=0;j<vec1.size();j++){
        vec1[j]+=vec2[j];
        if(vec1[j]>=10){
            vec1[j+1]+=vec1[j]/10;
            vec1[j]%=10;
        }
    }
    while(vec1.size()>0 && vec1.back()==0)vec1.pop_back();
    if((int)vec1.size()==0)vec1.pb(0);
    return vec1;
}
vector<int> mul(vector<int> vec1,vector<int> vec2){
    vector<int> ret(vec1.size()+vec2.size()+10,0);
    for(int i=0;i<vec1.size();i++){
        for(int j=0;j<vec2.size();j++){
            ret[i+j]+=vec1[i]*vec2[j];
        }
    }
    for(int i=0;i<ret.size();i++){
        if(ret[i]>=10){
            ret[i+1]+=ret[i]/10;
            ret[i]%=10;
        }
    }
    while(ret.size()>0 && ret.back()==0)ret.pop_back();
    if(ret.size()==0)ret.pb(0);
    return ret;
}

vector<int> dv2(vector<int> vec){
    vec[0]=vec[0]/2;
    for(int i=1;i<vec.size();i++){
        int ret=5*vec[i];
        vec[i-1]+=ret;
        vec[i]=0;
    }
    vec.pb(0);
    for(int i=0;i<vec.size();i++){
        if(vec[i]>=10){
            vec[i+1]+=vec[i]/10;
            vec[i]%=10;
        }
    }
    while(vec.size()>0 && vec.back()==0)vec.pop_back();
    if(vec.size()==0)vec.pb(0);
    return vec;
}


bool ls(vector<int> a,vector<int> b){
    if(b.size()>a.size())return 1;
    if(a.size()>b.size())return 0;
    for(int i=a.size()-1;i>=0;i--){
        if(b[i]>a[i])return 1;
        if(a[i]>b[i])return 0;
    }
    return 0;
}

bool lseq(vector<int> a,vector<int> b){
    if(b.size()>a.size())return 1;
    if(a.size()>b.size())return 0;
    for(int i=a.size()-1;i>=0;i--){
        if(b[i]>a[i])return 1;
        if(a[i]>b[i])return 0;
    }
    return 1;
}


vector<int> sub(vector<int> a,vector<int> b){
    while(b.size()<a.size())b.pb(0);
    for(int i=a.size()-1;i>=1;i--){
        if(a[i]>b[i]){
            a[i]--;
            a[i-1]+=10;
        }
    }
    for(int i=0;i<a.size();i++){
        a[i]-=b[i];
    }
    for(int i=0;i<a.size();i++){
        if(a[i]>=10){
            a[i+1]+=a[i]/10;
            a[i]%=10;
        }
    }
    while(a.size()>0 && a.back()==0)a.pop_back();
    if(a.size()==0)a.pb(0);
    return a;
}
