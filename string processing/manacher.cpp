#include<bits/stdc++.h>
using namespace std;

void manacher(string t,vector<int>& even,vector<int>& odd){
    // even[i] is the maximum x such that sub[i-x+1,i+x] is a palindrome
    // odd[i] is the maximum x such that sub[i-x+1,i+x-1] is a palindrome
    auto init=[](string t){
        string nw="#";
        for(auto v:t){nw+=v;nw+="#";}
        return nw;
    };
    string s=init(t);
    int n=s.size();
    s="$"+s+"^";
    vector<int> p(n+2,0);
    int l=1,r=1;
    for(int i=1;i<=n;i++){
        p[i]=max(0,min(r-i,p[l+(r-i)]));
        while(s[i-p[i]]==s[i+p[i]])p[i]++;
        if(i+p[i]>r)l=i-p[i],r=i+p[i];
    }
    p=vector<int>(begin(p)+1,end(p)-1);
    even=odd=vector<int>((int)t.size(),0);
    for(int i=1;i<p.size()-1;i++){
        if(i%2==1)odd[i/2]=(p[i]+1)/2;
        else even[(i-1)/2]=p[i]/2;
    }
    // for(auto v:odd)cout<<v<<" ";cout<<"\n";
    // for(auto v:even)cout<<v<<" ";cout<<"\n";
}