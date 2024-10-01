struct Trie {
    struct node {
        node *ch[2];
        int freq;
        node(){ch[0]=ch[1]=nullptr,freq=0;}
    };
    node *root;
    const int sz=20;
    Trie() {root=nullptr;}

    void update(int val,int add) {
        if(!root)root=new node();
        node *cur=root;
        for(int i=sz-1;i>=0;i--) {
            int bt=((val>>i)&1);
            cur->freq+=add;
            if(!cur->ch[bt])cur->ch[bt]=new node();
            cur=cur->ch[bt];
        }
        cur->freq+=add;
    }
    int greater_or_equal(int val) {
        if(!root)return 0;
        node *cur=root;
        int ans=0;
        for(int i=sz-1;i>=0;i--) {
            int bt=((val>>i)&1);
            if(bt==0 && cur->ch[1]) ans+=cur->ch[1]->freq;
            if(!cur->ch[bt])return ans;
            cur=cur->ch[bt];
        }
        return ans+cur->freq;
    }
};