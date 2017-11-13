#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=2e5+10;
int num;
LL ans;
LL liner[65];
LL a[N],_xor[N];
struct Edge
{
    int next,to;
    LL val;
    int rev;
}edge[N*2];
int head[N],ecnt;
int pre[N];
void addedge(int u,int v,LL d)
{
    edge[++ecnt]=(Edge){head[u],v,d};
    head[u]=ecnt;
    edge[++ecnt]=(Edge){head[v],u,d};
    head[v]=ecnt;
    edge[head[u]].rev=head[v];
    edge[head[v]].rev=head[u];
    return ;
}
int n,m,T,t,u,v,cnt;
LL p;
void init()
{
    clr(pre);
    clr_1(head);
    ecnt=0;
    cnt=0;
    clr(liner);
    return ;
}
void dfs(int u,int fa)
{
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int t=edge[i].to;
        if(edge[i].rev!=fa)
        {
            if(!pre[t])
            {
                pre[t]=u;
                _xor[t]=_xor[u]^edge[i].val;
                dfs(t,i);
            }
            else
            {
                a[++cnt]=_xor[u]^edge[i].val^_xor[t];
            }
        }
    }
    return ;
}
int main()
{
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&u,&v,&p);
        addedge(u,v,p);
    }
    pre[1]=1;
    _xor[1]=0;
    dfs(1,0);
    for(int i=1;i<=cnt;i++)
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
            if((liner[i]>>j)&1) liner[i]^=liner[j];
    }
    ans=_xor[n];
    for(int i=62;i>=0;i--)
    {
        ans=max(ans,liner[i]^ans);
    }
    printf("%lld\n",ans);
    return 0;
}
