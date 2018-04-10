#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=2e5+10;
const int M=5e6+10;
struct edg
{
    int next,to;
}edge[N<<1];
int head[N],ecnt;
void addedge(int u,int v)
{
    edge[++ecnt]=(edg){head[u],v};
    head[u]=ecnt;
    return ;
}
struct Seg
{
    int l,r;
    int sum,maxn;
    int lt,rt;
}seg[M];
int num[N],son[N],dfstm[N],pre[N],last[N],fa[N],top[N],deep[N],root[N];
int n,m,p,q,T,cnt,k,u,scnt;
int v;
int c[N];
int w[N];
char op[10];
int makenode(int l,int r)
{
    seg[++scnt]=(Seg){l,r,0,0,0,0};
    return scnt;
}
void pushdown(int i)
{
    if(seg[i].lt==0)
        seg[i].lt=makenode(seg[i].l,(seg[i].l+seg[i].r)>>1);
    if(seg[i].rt==0)
        seg[i].rt=makenode(((seg[i].l+seg[i].r)>>1)+1,seg[i].r);
    return ;
}
void pushup(int i)
{
    seg[i].maxn=max(seg[seg[i].lt].maxn,seg[seg[i].rt].maxn);
    seg[i].sum=seg[seg[i].lt].sum+seg[seg[i].rt].sum;
    return ;
}
void update(int i,int pos,int val)
{
    if(seg[i].l==pos && seg[i].r==pos)
    {
        seg[i].maxn=seg[i].sum=val;
        return ;
    }
    pushdown(i);
    int mid=(seg[i].l+seg[i].r)>>1;
    if(pos<=mid)
        update(seg[i].lt,pos,val);
    else
        update(seg[i].rt,pos,val);
    pushup(i);
    return ;
}
int querysum(int i,int l,int r)
{
    if(!i)
        return 0;
    if(seg[i].l>=l && seg[i].r<=r)
    {
        return seg[i].sum;
    }
    int mid=(seg[i].l+seg[i].r)>>1;
    int ans=0;
    if(mid>=l)
        ans+=querysum(seg[i].lt,l,r);
    if(mid<r)
        ans+=querysum(seg[i].rt,l,r);
    return ans;
}
int querymaxn(int i,int l,int r)
{
    if(!i)
        return 0;
    if(seg[i].l>=l && seg[i].r<=r)
    {
        return seg[i].maxn;
    }
    int mid=(seg[i].l+seg[i].r)>>1;
    int ans=0;
    if(mid>=l)
        ans=max(ans,querymaxn(seg[i].lt,l,r));
    if(mid<r)
        ans=max(ans,querymaxn(seg[i].rt,l,r));
    return ans;
}
int getmaxn(int u,int v)
{
    int tpu=top[u],tpv=top[v];
    int rt=root[c[v]];
    int ans=0;
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(u,v);
            swap(tpu,tpv);
        }
        ans=max(ans,querymaxn(rt,pre[tpu],pre[u]));
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]>deep[v]) swap(u,v);
    ans=max(ans,querymaxn(rt,pre[u],pre[v]));
    return ans;
}
int getsum(int u,int v)
{
    int tpu=top[u],tpv=top[v];
    int rt=root[c[v]];
    int ans=0;
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(u,v);
            swap(tpu,tpv);
        }
        ans+=querysum(rt,pre[tpu],pre[u]);
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]>deep[v]) swap(u,v);
    ans+=querysum(rt,pre[u],pre[v]);
    return ans;
}
void inito()
{
    clr_1(head);
    clr_1(son);
    clr(root);
    ecnt=cnt=scnt=0;
    fa[1]=1;
    deep[1]=1;
    top[1]=1;
    seg[0]=(Seg){1,n,0,0,0,0};
    return ;
}
void dfs1(int u)
{
    int p;
    num[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        p=edge[i].to;
        if(p!=fa[u])
        {
            fa[p]=u;
            deep[p]=deep[u]+1;
            dfs1(p);
            num[u]+=num[p];
            if(son[u]==-1||num[son[u]]<num[p])
                son[u]=p;
        }
    }
    return ;
}
void dfs2(int u)
{
    pre[u]=++cnt;
    dfstm[cnt]=u;
    if(son[u]!=-1)
    {
        top[son[u]]=top[u];
        dfs2(son[u]);
    }
    int p;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        p=edge[i].to;
        if(p!=fa[u] && p!=son[u])
        {
            top[p]=p;
            dfs2(p);
        }
    }
    last[u]=cnt;
    return ;
}
int main()
{
    scanf("%d%d",&n,&q);
    inito();
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&c[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1);
    dfs2(1);
    for(int i=1;i<=n;i++)
    {
        update(root[c[i]]?root[c[i]]:(root[c[i]]=makenode(1,n)),pre[i],w[i]);
    }
    for(int i=1;i<=q;i++)
    {
        scanf("%s%d%d",op,&u,&v);
        if(op[0]=='C')
            if(op[1]=='C')
            {
                update(root[c[u]],pre[u],0);
                c[u]=v;
                update(root[c[u]]?root[c[u]]:(root[c[u]]=makenode(1,n)),pre[u],w[u]);
            }
            else
            {
                w[u]=v;
                update(root[c[u]],pre[u],w[u]);
            }
        else
            if(op[1]=='S')
            {
                printf("%d\n",getsum(u,v));
            }
            else
            {
                printf("%d\n",getmaxn(u,v));
            }
    }
    return 0;
}


