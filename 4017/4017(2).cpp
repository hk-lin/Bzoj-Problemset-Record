#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 998244353
using namespace std;
const int N=1e5+10;
int bit[N];
LL a[N];
LL order[N],found[N];
int n,m,k,cnt;
LL ans1,ans2;
void qy1(int mp)
{
    LL num=0;
    LL now=0;
    for(int i=1;i<=n;i++)
    {
        now^=(a[i]>>mp)&1;
        if(now)
            num++;
    }
    ans1=(ans1+num*(n-num+1)%mod*(1LL<<mp)%mod)%mod;
    return ;
}
void add(int i,int x)
{
    if(!i) return ;
    while(i<=cnt+1)
    {
        bit[i]^=x;
        i+= i&-i;
    }
    return ;
}
int sum(int i)
{
    int res=0;
    while(i)
    {
        res^=bit[i];
        i-= i&-i;
    }
    return res;
}
void qy2(int mp)
{
    clr(bit);
    int p;
    found[0]=order[0]=0;
    for(int i=1;i<=n;i++)
    {
        found[i]=(found[i-1]+a[i])%(1LL<<(mp+1));
        order[i]=found[i];
    }
    sort(order,order+n+1);
    cnt=unique(order,order+n+1)-order-1;
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        p=lower_bound(order,order+cnt+1,found[i])-order;
        if(order[p]!=found[i]) p--;
        p++;
        add(p,1);
        ans^=sum(p);
        p=lower_bound(order,order+cnt+1,found[i]-(1LL<<mp))-order;
        if(order[p]!=found[i]-(1LL<<mp)) p--;
        p++;
        ans^=sum(p);
        p=lower_bound(order,order+cnt+1,found[i]+(1LL<<mp))-order;
        if(p==cnt+1 || order[p]!=found[i]+(1LL<<mp)) p--;
        p++;
        ans^=sum(p);
    }
    if(ans) ans2|=(1LL<<mp);
    return ;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    ans1=ans2=0;
    for(int i=0;i<=20;i++) qy1(i);
    for(int i=0;i<=40;i++) qy2(i);
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}
