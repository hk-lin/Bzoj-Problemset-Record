#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=5e5+10;
LL gcd(LL a,LL b)
{
    LL c=0;
    while(b)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
struct Query
{
    int l,r,id,backet;
    LL fm,fz;
    void modify()
    {
        if(fz==0)
        {
            fm=1;
            fz=0;
        }
        else
        {
            LL g=gcd(fm,fz);
            fz/=g;
            fm/=g;
        }
        return ;
    }
}Q[N];
bool cmp(Query a,Query b)
{
    if(a.backet==b.backet) return a.r<b.r;
    return a.backet<b.backet;
}
LL ansfm[N],ansfz[N];
int n,m,q,k,col[N],sum[N];
void init()
{
    clr(sum);
    for(int i=1;i<=n;i++)
        scanf("%d",&col[i]);
    int dk=(int)sqrt(n+0.5);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].backet=(Q[i].l-1)/dk+1;
        Q[i].id=i;
    }
    sort(Q+1,Q+q+1,cmp);
    return ;
}
void add(int pos,LL &ans,int val)
{
    ans+=(LL)2*val*sum[col[pos]]+1;
    sum[col[pos]]+=val;
}
void solve()
{
    int l=1,r=0;
    LL ans=0;
    for(int i=1;i<=q;i++)
    {
        if(Q[i].r>r)
        {
            for(++r;r<=Q[i].r;r++)
                add(r,ans,1);
            r--;
        }
        if(Q[i].l<l)
        {
            for(--l;l>=Q[i].l;l--)
                add(l,ans,1);
            l++;
        }
        if(Q[i].l>l)
            for(l;l<Q[i].l;l++)
                add(l,ans,-1);
        if(Q[i].r<r)
            for(r;r>Q[i].r;r--)
                add(r,ans,-1);
        Q[i].fz=ans-(r-l+1);
        Q[i].fm=(LL)(r-l)*(r-l+1);
        Q[i].modify();
        ansfm[Q[i].id]=Q[i].fm;
        ansfz[Q[i].id]=Q[i].fz;
//        cout<<Q[i].id<<" "<<Q[i].l<<" "<<Q[i].r<<" "<<l<<" "<<r<<" "<<Q[i].fm<<" "<<Q[i].fz<<endl;
    }
    for(int i=1;i<=q;i++)
        printf("%lld/%lld\n",ansfz[i],ansfm[i]);
    return ;
}
int main()
{
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}
