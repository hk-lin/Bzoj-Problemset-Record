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
}edge[N<<1];
int head[N],ecnt;
int col[N];
void addedge(int u,int v)
{
    edge[++ecnt]=(edg){head[u],v};
    head[u]=ecnt;
    return ;
}
struct Seg
{
    int l,r;
    int tag,col;
    int ltag,rtag;
}seg[N<<2];
int num[N],son[N],dfstm[N],pre[N],last[N],fa[N],top[N],deep[N];
int n,m,p,q,u,v,T,cnt,k;
char op[10];
void pushdown(int i)
{
    if(seg[i].tag)
    {
        if(seg[i].l!=seg[i].r)
        {
            seg[i<<1].tag=seg[i<<1|1].tag=1;
            seg[i<<1].col=seg[i<<1|1].col=1;
            seg[i<<1].ltag=seg[i<<1].rtag=seg[i<<1|1].ltag=seg[i<<1|1].rtag=seg[i].ltag;
        }
        seg[i].tag=0;
    }
    return ;
}
void pushup(int i)
{
    seg[i].col=seg[i<<1].col+seg[i<<1|1].col;
    if(seg[i<<1].rtag==seg[i<<1|1].ltag)
        seg[i].col--;
    seg[i].ltag=seg[i<<1].ltag;
    seg[i].rtag=seg[i<<1|1].rtag;
    return ;
}
void init(int i,int l,int r)
{
    seg[i]=(Seg){l,r,0};
    if(l==r)
    {
        seg[i].rtag=seg[i].ltag=col[dfstm[l]];
        seg[i].col=1;
        return ;
    }
    int mid=(l+r)>>1;
    init(i<<1,l,mid);
    init(i<<1|1,mid+1,r);
    pushup(i);
    return ;
}
void update(int i,int l,int r,int val)
{
    if(seg[i].l>=l && seg[i].r<=r)
    {
        seg[i].tag=1;
        seg[i].ltag=seg[i].rtag=val;
        seg[i].col=1;
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
    pushup(i);
    return ;
}
int query(int i,int l,int r)
{
    if(seg[i].l>=l && seg[i].r<=r)
    {
        return seg[i].col;
    }
    pushdown(i);
    int mid=(seg[i].l+seg[i].r)>>1;
    int ans=0;
    if(mid<l)
    {
        ans=query(i<<1|1,l,r);
    }
    else if(mid>=r)
    {
        ans=query(i<<1,l,r);
    }
    else
    {
        ans=query(i<<1,l,r)+query(i<<1|1,l,r);
        if(seg[i<<1].rtag==seg[i<<1|1].ltag)
            ans--;
    }
    return ans;
}
int getstag(int i,int pos)
{
    if(seg[i].r==pos)
        return seg[i].rtag;
    if(seg[i].l==pos)
        return seg[i].ltag;
    pushdown(i);
    int mid=(seg[i].l+seg[i].r)>>1;
    if(mid<pos)
        return getstag(i<<1|1,pos);
    else
        return getstag(i<<1,pos);
}
void inito()
{
    clr_1(head);
    clr_1(son);
    ecnt=cnt=0;
    fa[1]=1;
    deep[1]=1;
    top[1]=1;
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
void change(int u,int v,int val)
{
    int tpu=top[u],tpv=top[v];
    while(tpu!=tpv)
    {
        if(deep[tpu]<deep[tpv])
        {
            swap(tpu,tpv);
            swap(u,v);
        }
        update(1,pre[tpu],pre[u],val);
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]>deep[v]) swap(u,v);
    update(1,pre[u],pre[v],val);
    return ;
}
int getans(int u,int v)
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
        ans+=query(1,pre[tpu],pre[u]);
        if(getstag(1,pre[tpu])==getstag(1,pre[fa[tpu]]))
            ans--;
        u=fa[tpu];
        tpu=top[u];
    }
    if(deep[u]>deep[v]) swap(u,v);
    ans+=query(1,pre[u],pre[v]);
    return ans;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        inito();
        for(int i=1;i<=n;i++)
            scanf("%d",&col[i]);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        dfs1(1);
        dfs2(1);
        init(1,1,n);
        for(int i=1;i<=m;i++)
        {
            scanf("%s",op);
            if(op[0]=='Q')
            {
                scanf("%d%d",&u,&v);
                printf("%d\n",getans(u,v));
            }
            if(op[0]=='C')
            {
                scanf("%d%d%d",&u,&v,&k);
                change(u,v,k);
            }
        }
    }
    return 0;
}
