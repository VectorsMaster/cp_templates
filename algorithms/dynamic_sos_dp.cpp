#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;


struct SOS_Bag {
    int left,right;
    vector<vector<LL>> sos_sum;
    vector<int> pw3;
    vector<vector<int>> ternaries;

    SOS_Bag(){}
    SOS_Bag(int k) { // remember to set left according to the problem statement
        left=min(k/2,7),right=k-left;

        pw3.pb(1);
        while(pw3.size()<=left)pw3.pb(pw3.back()*3);
        sos_sum=vector<vector<LL>>(pw3[left],vector<LL>((1<<right),0LL));
        ternaries=vector<vector<int>>((1<<left),vector<int>());

        for(int trn=0;trn<pw3[left];trn++) {
            for(int bnr=0;bnr<(1<<left);bnr++) {
                bool ok=true;
                int tnr_copy=trn;
                for(int bt=0;bt<left;bt++) {
                    int t_md=tnr_copy%3;
                    tnr_copy/=3;
                    int b_md=((bnr>>bt)&1);
                    if(b_md && !t_md){ok=false;break;}
                    if(!b_md && t_md==2){ok=false;break;}
                }
                if(ok) ternaries[bnr].pb(trn);
            }
        }
    }
    void update(int mask,int to_add) {
        int l_part=(mask&((1<<left)-1));
        int r_part=(mask>>left);
        for(auto ternary_mask:ternaries[l_part]) {
            sos_sum[ternary_mask][r_part]+=to_add;
        }
    }

    LL query(int sub_mask,int super_mask) {
        if((super_mask&sub_mask)!=sub_mask)return 0;
        int super_r=(super_mask>>left);
        int sub_r=(sub_mask>>left);
        int ternary_mask=0;
        for(int i=0;i<left;i++) {
            if((sub_mask&(1<<i)))ternary_mask+=(pw3[i]<<1);
            else if((super_mask&(1<<i))) ternary_mask+=pw3[i];
        }

        LL ans=0;
        for(int r_mask=sub_r;r_mask<(1<<right);r_mask++) {
            if((r_mask&super_r)!=r_mask)continue;
            if((r_mask&sub_r)!=sub_r)continue;
            ans+=sos_sum[ternary_mask][r_mask];
        }
        return ans;
    }
};