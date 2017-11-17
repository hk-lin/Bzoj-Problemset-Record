#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=3e4+10;

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

int val[N],n,m,q,T,u,v,cnt;
int fa[N],top[N],num[N],son[N],deep[N],dfstm[N],id[N];
char s[20];
struct Seg//带有求和和求最大值的线段树
{
    int l,r,maxn,sum;
}seg[N<<2];
void init(int i,int l,int r)//初始化线段树
{
    seg[i]=(Seg){l,r};
    if(l==r)
    {
        seg[i].maxn=seg[i].sum=val[dfstm[l]];
        return ;
    }
    int mid=(l+r)>>1;
    init(i<<1,l,mid);
    init(i<<1|1,mid+1,r);
    seg[i].maxn=max(seg[i<<1].maxn,seg[i<<1|1].maxn);
    seg[i].sum=seg[i<<1].sum+seg[i<<1|1].sum;
    return ;
}
void update(int i,int pos,int value)//更新pos点的权值带来sum和马鑫改变
{
    if(seg[i].r==pos && seg[i].l==pos)
    {
        seg[i].sum=seg[i].maxn=value;
        return ;
    }
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid>=pos)
    {
        update(i<<1,pos,value);
    }
    if(mid<pos)
    {
        update(i<<1|1,pos,value);
    }
    seg[i].maxn=max(seg[i<<1].maxn,seg[i<<1|1].maxn);
    seg[i].sum=seg[i<<1].sum+seg[i<<1|1].sum;
    return ;
}
int querysum(int i,int l,int r)//询问一个线段树区间[L,R]的和
{
    if(seg[i].l>=l &&seg[i].r<=r)
    {
        return seg[i].sum;
    }
    int ans=0;
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid>=l)
        ans+=querysum(i<<1,l,r);
    if(mid<r)
        ans+=querysum(i<<1|1,l,r);
    return ans;
}
int querymax(int i,int l,int r)//询问一个线段树区间[L,R]的最大值
{
    if(seg[i].l>=l &&seg[i].r<=r)
    {
        return seg[i].maxn;
    }
    int ans=-0x3f3f3f3f;
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid>=l)
        ans=max(ans,querymax(i<<1,l,r));
    if(mid<r)
        ans=max(ans,querymax(i<<1|1,l,r));
    return ans;
}
int querys(int u,int v)//询问树上u到v的和
{
    int tpu=top[u],tpv=top[v];
    int ans=0;
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(tpu,tpv);
            swap(u,v);
        }
        ans+=querysum(1,id[tpu],id[u]);
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]<deep[v]) swap(u,v);
    ans+=querysum(1,id[v],id[u]);
    return ans;
}
int querym(int u,int v)//询问树上u到v的最大值
{
    int tpu=top[u],tpv=top[v];
    int ans=-0x3f3f3f3f;
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(tpu,tpv);
            swap(u,v);
        }
        ans=max(ans,querymax(1,id[tpu],id[u]));
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]<deep[v]) swap(u,v);
    ans=max(ans,querymax(1,id[v],id[u]));
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
    id[u]=++cnt;
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
    return ;
}
int main()
{
    scanf("%d",&n);
    inito();
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    dfs1(1,1,1);
    dfs2(1,1);
    init(1,1,n);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%s%d%d",s,&u,&v);
        if(strcmp(s,"CHANGE")==0)
        {
            update(1,id[u],v);
        }
        if(strcmp(s,"QSUM")==0)
        {
            printf("%d\n",querys(u,v));
        }
        if(strcmp(s,"QMAX")==0)
        {
            printf("%d\n",querym(u,v));
        }
    }
    return 0;
}
