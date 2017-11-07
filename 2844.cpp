
#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define mod 10086
#define LL long long
using namespace std;
const int N=1e5+10;
LL a[N];
LL liner[65],per[65];
int n,m,k,q;
LL p,qy,tag,ans;
LL quick_pow(LL n,LL x)
{
    x=(x%mod+mod)%mod;
    LL res=1;
    while(n)
    {
        if(n&1) res=(res*x)%mod;
        n>>=1;
        x=(x*x)%mod;
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    clr(liner);
    for(int i=1;i<=n;i++)
    {
        p=a[i];
        for(int j=62;j>=0;j--)
        {
            if(p>>j)
            {
                if(liner[j]) p^=liner[j];
                else
                {
                    liner[j]=p;
                    break;
                }
            }
        }
    }
    for(int i=62;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
            if((liner[i]>>j)&1)
                liner[i]^=liner[j];
    }
    k=0;
    for(int i=62;i>=0;i--)
        if(liner[i])
            per[++k]=liner[i];
    scanf("%lld",&p);
    ans=0;
    for(int i=1;i<=k;i++)
    {
        ans<<=1;
        if((p^per[i])<p)
        {
            ans|=1;
            p^=per[i];
        }
//        cout<<i<<" "<<ans<<" "<<p<<endl;
    }
//    cout<<n<<" "<<k<<" "<<ans<<endl;
    printf("%lld\n",(ans%mod*quick_pow((LL)(n-k),2)%mod+1)%mod);
    return 0;
}
