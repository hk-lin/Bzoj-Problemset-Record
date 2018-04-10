#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
//usually mod num is 1004535809 99824435 1000000007
#define pnum 233
#define INF 0x3f3f3f3f
using namespace std;
const int N=1e6+10;
int f[N],power[N][2],hash[N][2],mod[2]={1004535809,99824435};
inline int gethash(int l,int r,int x)
{
    return (hash[r][x]-(LL)hash[l-1][x]*power[r-l+1][x]%mod[x]+mod[x])%mod[x];
}
inline bool check(int x,int y,int len)
{
    return gethash(x,x+len-1,0)==gethash(y,y+len-1,0) && gethash(x,x+len-1,1)==gethash(y,y+len-1,1);
}
int n,ans;
char s[N];
int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    power[0][0]=power[0][1]=1;
    hash[0][0]=hash[0][1]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<2;j++)
        {
            power[i][j]=(LL)power[i-1][j]*pnum%mod[j];
            hash[i][j]=((LL)hash[i-1][j]*pnum+(s[i-1]-'a'))%mod[j];
        }
    f[n/2+1]=0;
    ans=0;
    for(int i=n/2;i>=1;i--)
    {
        f[i]=min(f[i+1]+2,n/2-i+1);
        while(f[i] && !check(i,n-i-f[i]+2,f[i])) f[i]--;
        if(check(1,n-i+2,i-1))
            ans=max(f[i]+i-1,ans);
    }
    printf("%d\n",ans);
    return 0;
}
