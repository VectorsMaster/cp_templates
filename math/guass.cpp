#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;

int gauss_mod2 (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
    // m number of variables
    // n number of equations 
    // each equations has n variable and one answer (a[i] has m+1 size for all 0 <= i < n)
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;
        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }
    for(int i=0;i<m;i++){
        if(where[i]!=-1){
            ans[i]=a[where[i]][m];
        }
    }
    for(int i=0;i<n;i++){
        int xr=0;
        for(int j=0;j<m;j++){
            xr=(xr^(ans[j]&a[i][j]));
        }
        if(xr!=a[i][m]){
            return 0;
        }
    }
    for(int i=0;i<m;i++){
        if(where[i]==-1)return 2;
    }
    return 1;
}


int gauss (vector <vector<int>> &a, vector<int> & ans) {
    int n=(int)a.size();
    int m=(int)a[0].size()-1;
    vector<int> where(m, -1);
    for (int col=0,row=0;col<m&&row<n;col++) {
        int sel=row;
        for(int i=row;i<n;i++)if(a[i][col]!=0)sel = i;
        if (a[sel][col]==0)continue;
        for (int i=col;i<=m;i++)swap (a[sel][i], a[row][i]);
        where[col] = row;
        for (int i=0;i<n;i++){
            if(i==row)continue;
            int c = mul(a[i][col],poow(a[row][col],MOD-2));
            for (int j=col;j<=m;j++)
            a[i][j]=sub(a[i][j],mul(a[row][j],c));
        }
        row++;
    }
 
    ans.assign(m,0);
    for (int i=0; i<m; ++i){
        if(where[i]==-1)continue;
        ans[i]=mul(a[where[i]][m],poow(a[where[i]][i],MOD-2));
    }
    for (int i=0; i<n; ++i) {
        int sum=0;
        for (int j=0; j<m; ++j)
            sum=add(sum,mul(ans[j],a[i][j]));
        if (sum!=a[i][m])return 0;
    }
    for (int i=0; i<m; ++i)if(where[i] == -1)return 2;
    return 1;
}