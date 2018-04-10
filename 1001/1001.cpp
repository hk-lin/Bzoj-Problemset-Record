#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define mod 1000000007
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
const int N=1e3+10;
LL heng[N][N],shu[N][N],xie[N][N];
LL ptmin[N][N];
int n,m,T,k;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
            scanf("%lld",&heng[i][j]);
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&shu[i][j]);
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            scanf("%lld",&xie[i][j]);
    for(int i=2;i<=n+m;i++)
    {
        for(int j=i>m+1?i-m:1;j<=n && i-j>=1;j++)
        {
             k=i-j;
             ptmin[j][k]=0;
             if(j-1>0)
                ptmin[j][k]+=min(ptmin[j-1][k],shu[j-1][k]);
            if(k-1>0)
                ptmin[j][k]+=min(ptmin[j][k-1],heng[j][k-1]);
            if(k-1>0 && j-1>0)
                ptmin[j][k]+=min(ptmin[j-1][k-1],xie[j-1][k-1]);
        }
    }
    printf("%lld\n",ptmin[n][m]);
}
