#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=1e5+10;

struct edg
{
    int next,to;
}edge[N*2];
int head[N],ecnt;
void addedge(int u,int v)
{
    edge[++ecnt]=(edg){head[u],v};
    head[u]=ecnt;
    return ;
}

LL val[N];
int n,m,q,T,u,v,cnt;
int fa[N],top[N],num[N],son[N],deep[N],dfstm[N],pre[N],last[N];
int op;
struct Seg//带有求和和求最大值的线段树
{
    int l,r;
    LL sum,tag;
}seg[N<<2];
void init(int i,int l,int r)//初始化线段树
{
    seg[i]=(Seg){l,r,0};
    if(l==r)
    {
        seg[i].sum=val[dfstm[l]];
        return ;
    }
    int mid=(l+r)>>1;
    init(i<<1,l,mid);
    init(i<<1|1,mid+1,r);
    seg[i].sum=seg[i<<1].sum+seg[i<<1|1].sum;
    return ;
}
void pushdown(int i)
{
    if(seg[i].tag!=0)
    {
        if(seg[i].l!=seg[i].r)
        {
            seg[i<<1].tag+=seg[i].tag;
            seg[i<<1|1].tag+=seg[i].tag;
            seg[i<<1].sum+=(seg[i<<1].r-seg[i<<1].l+1)*seg[i].tag;
            seg[i<<1|1].sum+=(seg[i<<1|1].r-seg[i<<1|1].l+1)*seg[i].tag;
        }
        seg[i].tag=0;
    }
    return ;
}
void update(int i,int l,int r,LL val)//更新[l,r]的权值带来sum改变
{
    if(seg[i].l>=l && seg[i].r<=r)
    {
        seg[i].tag+=val;
        seg[i].sum+=(seg[i].r-seg[i].l+1)*val;
        return ;
    }
    pushdown(i);
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid>=l)
    {
        update(i<<1,l,r,val);
    }
    if(mid<r)
    {
        update(i<<1|1,l,r,val);
    }
    seg[i].sum=seg[i<<1].sum+seg[i<<1|1].sum;
    return ;
}
LL querysum(int i,int l,int r)//询问一个线段树区间[L,R]的和
{
    if(seg[i].l>=l &&seg[i].r<=r)
    {
        return seg[i].sum;
    }
    pushdown(i);
    LL ans=0;
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid>=l)
        ans+=querysum(i<<1,l,r);
    if(mid<r)
        ans+=querysum(i<<1|1,l,r);
    return ans;
}
LL querys(int u,int v)//询问树上u到v的和
{
    int tpu=top[u],tpv=top[v];
    LL ans=0;
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(tpu,tpv);
            swap(u,v);
        }
        ans+=querysum(1,pre[tpu],pre[u]);
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]<deep[v]) swap(u,v);
    ans+=querysum(1,pre[v],pre[u]);
    return ans;
}
void inito()
{
    clr_1(head);
    clr_1(son);
    ecnt=0;
    cnt=0;
    return ;
}
void dfs1(int u,int pre,int dep)
{
    num[u]=1;
    deep[u]=dep;
    fa[u]=pre;
    int p;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        p=edge[i].to;
        if(p!=pre)
        {
            dfs1(p,u,dep+1);
            num[u]+=num[p];
            if(son[u]==-1 || num[p]>num[son[u]])
                son[u]=p;
        }
    }
    return ;
}
void dfs2(int u,int tp)
{
    top[u]=tp;
    pre[u]=++cnt;
    dfstm[cnt]=u;
    if(son[u]!=-1)
        dfs2(son[u],tp);
    int p;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        p=edge[i].to;
        if(p!=fa[u] && p!=son[u])
            dfs2(p,p);
    }
    last[u]=cnt;
    return ;
}
int main()
{
    scanf("%d%d",&n,&q);
    inito();
    for(int i=1;i<=n;i++)
        scanf("%lld",&val[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,1,1);
    dfs2(1,1);
    init(1,1,n);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&op);
        if(op==3)
        {
            scanf("%d",&u);
            printf("%lld\n",querys(1,u));
        }
        if(op==2)
        {
            scanf("%d%d",&u,&v);
            update(1,pre[u],last[u],(LL)v);
        }
        if(op==1)
        {
            scanf("%d%d",&u,&v);
            update(1,pre[u],pre[u],(LL)v);
        }
    }
    return 0;
}
