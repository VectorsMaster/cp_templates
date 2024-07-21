#include<bits/stdc++.h>
using namespace std;
#define S second
#define F first


// data structure that supports:
// 1. add element to the end.
// 2. remove an element from the beginning.
// 3. get minimum/maximum among all present values.
struct MinMaxWindow {
    struct MinMaxStack {
        struct opt {int mn,mx;};
        stack<pair<int,opt>> s;
        bool empty() const {
            return s.empty();
        }
        int get_minimum() {
            return s.top().S.mn;
        }
        int get_maximum() {
            return s.top().S.mx;
        }
        void add_element(int new_element) {
            int minimum=(s.empty()?new_element:min(new_element,s.top().S.mn));
            int maximum=(s.empty()?new_element:max(new_element,s.top().S.mx));
            s.push({new_element,{minimum,maximum}});
        }
        int remove_element() {
            int removed_element=s.top().F;
            s.pop();
            return removed_element;
        }
    };
    MinMaxStack s1,s2;
    bool empty() {return s1.empty() && s2.empty();}
    int get_minimum() {
        if(s1.empty() || s2.empty()) {
            return (s1.empty()?s2.get_minimum():s1.get_minimum());
        }
        return min(s1.get_minimum(),s2.get_minimum());
    }
    int get_maximum() {
        if(s1.empty() || s2.empty()) {
            return (s1.empty()?s2.get_maximum():s1.get_maximum());
        }
        return max(s1.get_maximum(),s2.get_maximum());
    }
    void add_element(int new_element) {s1.add_element(new_element);}
    int remove_element() {
        if(s2.empty()) {
            while(!s1.empty()) {
                int element=s1.remove_element();
                s2.add_element(element);
            }
        }
        return s2.remove_element();
    }
};