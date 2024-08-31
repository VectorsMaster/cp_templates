#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define LL long long
#define pb push_back
#define F first
#define S second

const double PI=3.1415926;
const int KL=1e6;

using namespace std;

struct node{
    int freq;
    node *l,*r;
    node(){freq=0;l=r=this;}
    node(int q,node *lft,node *rt){freq=q;l=lft;r=rt;}
};
node *Empty=new node;
node  *insert(node *root,int val,int add,int st=0,int en=1e9){
    if(val<st || val>en)return root;
    if(st==en)return new node(root->freq+add,Empty,Empty);
    int mid=(st+en)/2;
    node *rt1=insert(root->l,val,add,st,mid);
    node *rt2=insert(root->r,val,add,mid+1,en);
    return new node(rt1->freq+rt2->freq,rt1,rt2);
}
int query(node *root,int lq,int rq,int st=0,int en=1e9){
    if(st>rq || en<lq)return 0;
    if(lq<=st && en<=rq)return root->freq;
    int mid=(st+en)/2;
    return query(root->l,lq,rq,st,mid)+query(root->r,lq,rq,mid+1,en);
}
struct Tree{
    int cnt;
    Tree *l,*r;
    Tree(){cnt=0,l=r=this;}
    Tree(int q,Tree *lft,Tree *rt){cnt=q;l=lft;r=rt;}
};Tree *Emty=new Tree;
Tree *insert2(Tree *root,int pos,int val,int st=0,int en=1e5+10){
    if(pos<st || pos>en)return root;
    if(st==en)return new Tree(val,Emty,Emty);
    int mid=(st+en)/2;
    Tree *rt1=insert2(root->l,pos,val,st,mid);
    Tree *rt2=insert2(root->r,pos,val,mid+1,en);
    return new Tree(max(rt1->cnt,rt2->cnt),rt1,rt2);
}
int fnd(Tree *root,int pos,int st=0,int en=1e5+10){
    if(root->cnt==0)return 0;
    if(st==en)return root->cnt;
    int mid=(st+en)/2;
    if(pos<=mid)return fnd(root->l,pos,st,mid);
    else return fnd(root->r,pos,mid+1,en);
}


int n,m,x,y,k,q;
node *roots[100002];
Tree *mp[100002];
string type,t;
map <string,int> vis;

int main()
{
    roots[0]=Empty;
    mp[0]=Emty;
    cin>>q;
    int cnt=0;
    for(int i=1;i<=q;i++){
        cin>>type;
        if(type=="set"){
            cin>>t>>x;
            if(vis[t]==0){cnt++;vis[t]=cnt;}
            int idx=vis[t];
            int val=fnd(mp[i-1],idx);
            if(val>0 && val!=x){
                roots[i]=insert(roots[i-1],val,-1);
                roots[i]=insert(roots[i],x,1);
            }
            else if(val==0)roots[i]=insert(roots[i-1],x,1);
            else roots[i]=roots[i-1];
            mp[i]=insert2(mp[i-1],idx,x);
        }
        else if(type=="remove"){
            cin>>t;
            if(vis[t]==0){cnt++,vis[t]=cnt;}
            int idx=vis[t];
            int val=fnd(mp[i-1],idx);
            if(val!=0)roots[i]=insert(roots[i-1],val,-1);
            else roots[i]=roots[i-1];
            mp[i]=insert2(mp[i-1],idx,0);
        }
        else if(type=="query"){
            cin>>t;
            if(vis[t]==0){cnt++;vis[t]=cnt;}
            int idx=vis[t];
            roots[i]=roots[i-1];
            int val=fnd(mp[i-1],idx);
            if(val==0)printf("-1\n");
            else printf("%d\n",query(roots[i],0,val-1));
            fflush(stdout);
            mp[i]=mp[i-1];
        }
        else {
            cin>>x;
            mp[i]=mp[i-x-1];
            roots[i]=roots[i-x-1];
        }
    }


    return 0;
}
