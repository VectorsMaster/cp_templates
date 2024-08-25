#include<bits/stdc++.h>
using namespace std;

#define LL long long
const LL MOD=998244353;
int mul(int x,int y){return x*1LL*y%MOD;}
int add(int x,int y){x+=y; if(x>=MOD)x-=MOD; return x;}
int sub(int x,int y){x-=y; if(x<0)x+=MOD; return x;}


// square matrix
struct Matrix {
    vector<vector<int>> A;
    int sz=0;
    Matrix(){}
    Matrix(int _sz,bool identity=false) {
        sz=_sz;
        A=vector<vector<int>>(sz,vector<int>(sz,0));
        if(identity) for(int i=0;i<sz;i++)A[i][i]=1;
    }
    Matrix operator *(Matrix other) {
        Matrix ret(sz);
        for(int i=0;i<sz;i++) {
            for(int j=0;j<sz;j++) {
                for(int k=0;k<sz;k++) {
                    ret.A[i][j]=add(ret.A[i][j],mul(A[i][k],other.A[k][j]));
                }
            }
        }
        return ret;
    }
};
Matrix matrix_power(Matrix mt,int n) {
    if(n==0)return Matrix(mt.sz,true);
    Matrix ret=matrix_power(mt,n/2);
    ret=ret*ret;
    if(n%2==1) ret=ret*mt;
    return ret;
}