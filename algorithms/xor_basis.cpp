#include<bits/stdc++.h>
using namespace std;

struct B{
    int lg=20,sz=0;
    vector<int> basis,actual_basis;
    B(){sz=0;}
    B(int _lg){
        lg=_lg;
        basis=vector<int>(lg,0);
        actual_basis=vector<int>(lg,0);
    }
    void insertVector(int mask,int st=0) {
        int act=mask;
        for(int i=st;i<lg;i++) {
            if((mask&1<<i)==0) continue;
            if(!basis[i]) {
                basis[i]=mask;
                actual_basis[i]=act;
                ++sz;
                return;
            }
            mask^=basis[i];
        }
    }
    // returns true if this mask can be resulted from current basis
    bool exists(int mask){
        for(int i=0;i<lg;i++) {
            if((mask&1<<i)==0)continue;
            if(!basis[i])return false;
            mask^=basis[i];
        }
        return true;
    }
};