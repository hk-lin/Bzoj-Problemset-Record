#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
#define INF 0x3f3f3f3f
using namespace std;
const int N=1e3+10;
int fa[N];
struct edg
{
    int u,v,val;
}edge[N*N];
int n,m,T,tot;
inline void addedge(int u,int v,int val)
{
    edge[++tot]=(edg){u,v,val};
    return ;
}
inline int Find(int x)
{
    if(fa[x]!=x) fa[x]=Find(fa[x]);
    return fa[x];
}
inline void Union(int x,int y)
{
    fa[Find(x)]=Find(y);
    return ;
}
bool cmp(edg a,edg b)
{
    return a.val<b.val;
}
int ans;
int main()
{
    scanf("%d",&n);
    tot=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        fa[i]=i;
        addedge(0,i,m);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&m);
            if(i<j)
                addedge(i,j,m);
        }
    sort(edge+1,edge+tot+1,cmp);
    ans=0;
    for(int i=1;i<=tot;i++)
    {
        if(Find(edge[i].u)!=Find(edge[i].v))
        {
            ans+=edge[i].val;
            Union(edge[i].u,edge[i].v);
        }
    }
    printf("%d\n",ans);
    return 0;
}
