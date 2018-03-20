#include <bits/stdc++.h>

using namespace std;


int ara[100005];
struct Tree
{
    int lf, lv, rf, rv, mf;
    Tree():lf(0),rf(0),lv(0),rv(0),mf(0){}
    Tree(int _lf,int _lv,int _rf,int _rv,int _mf):lf(_lf),rf(_rf),lv(_lv),rv(_rv),mf(_mf){}
}T[500005];


int Max(int a, int b,int c,int d,int e)
{
    return max(a, max(b, max(c,max(d, e))));
}
void build(int n,int b,int e)
{
    if(b==e) {  T[n]={1,ara[b],1,ara[b],1}; return ; }

    int lchild=n<<1;
    int rchild=n<<1|1;
    int mid=(b+e)>>1;
    build(lchild, b, mid);
    build(rchild, mid+1, e);

    if(T[lchild].lv == T[rchild].lv)
    {
        T[n].lf=T[lchild].lf+T[rchild].lf;
        T[n].lv=T[lchild].lv;
    }
    else
    {
        T[n].lf=T[lchild].lf;
        T[n].lv=T[lchild].lv;
    }

    if(T[lchild].rv == T[rchild].rv)
    {
        T[n].rf=T[lchild].rf+T[rchild].rf;
        T[n].rv=T[lchild].rv;
    }
    else
    {
        T[n].rf=T[rchild].rf;
        T[n].rv=T[rchild].rv;
    }

    if(T[lchild].rv == T[rchild].lv)
    {
        T[n].mf=T[lchild].rf+T[rchild].lf;

    }
    else T[n].mf=0;

    T[n].mf=Max(T[n].mf, T[lchild].mf, T[rchild].mf, T[n].rf, T[n].lf);
}
Tree query(int n,int b,int e,int l,int r)
{
    if(b>r||e<l) return Tree(0,0,0,0,0);
    if(b>=l&&e<=r) return T[n];

    int lchild=n<<1;
    int rchild=n<<1|1;
    int mid=(b+e)>>1;
    Tree p=query(lchild,b,mid,l,r);
    Tree q=query(rchild,mid+1,e,l,r);
    Tree ans;

    if(p.lv == q.lv)
    {
        ans.lf=p.lf+q.lf;
        ans.lv=p.lv;
    }
    else
    {
        ans.lf=p.lf;
        ans.lv=p.lv;
    }

    if(p.rv == q.rv)
    {
        ans.rf=p.rf+q.rf;
        ans.rv=p.rv;
    }
    else
    {
        ans.rf=q.rf;
        ans.rv=q.rv;
    }

    if(p.rv == q.lv)
    {
        ans.mf=p.rf+q.lf;
    }
    else
    {
        ans.mf=0;
    }
    ans.mf=Max(ans.mf,p.mf,q.mf,ans.lf,ans.rf);
    return ans;
}


int main()
{
    int n, q;


    while(scanf("%d", &n)==1 && n)
    {
        scanf("%d", &q);
        for(int i=1;i<=n;i++) scanf("%d", &ara[i]);

        memset(T,0,sizeof T);
        build(1,1,n);


        while(q--)
        {
            int l, r;
            scanf("%d%d",&l,&r);
            Tree ans=query(1,1,n,l,r);
            cout<<ans.mf<<endl;
        }
    }
    return 0;
}
