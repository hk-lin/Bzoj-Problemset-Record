#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL unsigned long long
#define mod 1000000007
using namespace std;
const int N=2e5+10;
LL a[N],liner[100],per[100];
bool f[40][40];
bool bits[40];
int n,m,k,cnt;
LL ans,res,keepbit;
void calc(int bit)
{
    clr(liner);
    LL p;
    for(int i=1;i<=n;i++)
    {
        for(int j=bit;j>=0;j--)
        {
            p=a[i];
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
    for(int i=bit;i>=0;i--)
    {
        for(int j=i-1;j>=0;j--)
            if((liner[i]>>j)&1) liner[j]^=liner[i];
    }
    cnt=0;
    for(int i=bit;i>=0;i--)
        if(liner[i])
            per[++cnt]=liner[i];
    return ;
}
void solve1(int n)
{
    ans=0,res=0;
    for(int i=1;i<=n;i++)
        ans|=a[i];
    if(ans&1)
        res=1;
    ans>>=1;
    return ;
}
void solve2(int n)
{
    clr(bits);
    ans=res=0;
    bool zero;
    for(int i=32;i>=0;i--)
    {
        zero=0;
        for(int j=1;j<=cnt;j++)
        {
            f[i][j]=(per[j]>>i)&1;
            zero|=f[i][j];
        }
        bits[i]=zero;
    }
    int p;
    for(int i=32;i>=0;i--)
        for(int j=32;j>=0;j--)
            if(bits[i]>0 && bits[j]>0)
            {
                p=1;
                for(int l=1;l<=cnt;l++)
                    if(f[i][l]^f[j][l])
                    {
                        p++;
                        break;
                    }
                if(i+j-p>=0)
                    ans+=(1LL<<(i+j-p));
                else
                {
                    res++;
                }
                ans+=res>>1;
                res&=1;
            }
    return ;
}

void dfs(int pos,LL num)
{

    if(pos>cnt)
    {
        //两位高精度计算u高位，v低位，因为这东西太大了。k>=3的情况下ans和res也算是一个高精度的高位和低位关系。
        LL u=0,v=1;
        for(int i=1;i<=k;i++)
        {
            u*=num;
            v*=num;
            u+=v>>cnt;
            v&=keepbit;
        }
        ans+=u;
        res+=v;
        ans+=res>>cnt;
        res&=keepbit;
        return ;
    }
    dfs(pos+1,num^per[pos]);
    dfs(pos+1,num);
    return ;
}
void solve3(int n,int k)
{
    ans=0;
    res=0;
    keepbit=(1LL<<cnt)-1;
    dfs(1,0);
    return ;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%llu",&a[i]);
    if(k==1)
        solve1(n);
    else if(k==2)
    {
        calc(32);
        solve2(n);
    }
    else
    {
        calc(61/k+1);
        solve3(n,k);
    }
    printf("%llu",ans);
    if(res) printf(".5");
    printf("\n");
    return 0;
}
