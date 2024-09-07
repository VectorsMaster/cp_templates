#include<map>
#include<vector>
#define LL long long
#define F first 
#define S second
#define pb push_back
using namespace std;

struct RangesDS {
    map<int,LL> st;
    RangesDS()= default;
    RangesDS(int N) {st[N+1]=-1;} // N+1 is first invalid index
    void clear(){st.clear();}
    void split(int index) {
        auto it=prev(st.upper_bound(index));
        if(it->F!=index){st[index]=it->S;}
    }
    void add_to_range(LL x,int l,int r) {
        split(l);
        split(r+1);
        for(auto it=st.find(l);it->F!=r+1;it++) it->S+=x;
    }
    void assign_range(LL x,int l,int r) {
        split(l);
        split(r+1);
        for(auto it=st.find(l);it->F!=r+1;it=st.erase(it))
            ;
        st[l]=x;
    }

    // optional queries
    vector<pair<pair<int,int>,LL>> go_through(int l,int r) {
        split(l);
        split(r+1);
        vector<pair<pair<int,int>,LL>> ret;
        for(auto it=st.find(l);it->F!=r+1;it++) {
            ret.pb({{it->F,next(it)->F-1},it->S});
        }
        return ret;
    }

};