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
void addedge(int u,int v)
{
    edge[++ecnt]=(edg){head[u],v};
    head[u]=ecnt;
    return ;
}
struct Seg
{
    int l,r;
    LL tag,sum;
}seg[N<<2];
int num[N],son[N],dfstm[N],pre[N],last[N],fa[N],top[N],deep[N];
LL val[N],x,fm[N];
int n,m,p,q,u,v,T,cnt,k;
double ans;
char op[10];
void pushdown(int i)
{
    if(seg[i].tag!=0)
    {
        if(seg[i].l!=seg[i].r)
        {
            seg[i<<1].tag+=seg[i].tag;
            seg[i<<1|1].tag+=seg[i].tag;
            seg[i<<1].sum+=(seg[i<<1].l-seg[i<<1].r+1)*seg[i].tag;
            seg[i<<1|1].sum+=(seg[i<<1|1].l-seg[i<<1|1].r+1)*seg[i].tag;
        }
        seg[i].tag=0;
    }
    return ;
}
void pushup(int i)
{
    seg[i].sum=seg[i<<1].sum+seg[i<<1|1].sum;
    return ;
}
void init(int i,int l,int r)
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
    pushup(i);
    return ;
}
void update(int i,int l,int r,LL val)
{
    if(seg[i].l>=l && seg[i].r<=r)
    {
        seg[i].tag+=val;
        seg[i].sum+=(seg[i].l-seg[i].r+1)*val;
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
        return seg[i].sum;
    }
    pushdown(i);
    int mid=(seg[i].l+seg[i].r)>>1;
    int ans=0;
    if(mid>=l)
    {
        ans+=query(i<<1,l,r);
    }
    if(mid<r)
    {
        ans+=query(i<<1|1,l,r);
    }
    return ans;
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
    cout<<u<<endl;
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
    fm[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        p=edge[i].to;
        if(p!=fa[u])
        {
            fm[u]+=(LL)num[p]*(LL)(num[u]-num[p]);
        }
    }
    fm[u]+=(LL)num[u]-1;
    fm[u]>>=1;
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
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&v);
        addedge(v,i);
        addedge(i,v);
    }
    for(int i=1;i<=n;i++)
        scanf("%lld",&val[i]);
    cout<<233<<endl;
    dfs1(1);
    cout<<233<<endl;
    dfs2(1);
    cout<<233<<endl;
    init(1,1,n);
    cout<<233<<endl;
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op);
        if(op[0]=='S')
        {
            scanf("%d%lld",&u,&x);
            update(1,pre[u],pre[u],x);
        }
        if(op[0]=='M')
        {
            scanf("%d%lld",&u,&x);
            update(1,pre[u],last[u],x);
        }
        if(op[0]=='Q')
        {
            scanf("%d",&u);
            ans=query(1,pre[u],pre[u])*(num[u]-1);
            for(int j=head[u];j!=-1;j=edge[j].next)
            {
                p=edge[j].to;
                if(p!=fa[u])
                {
                    ans+=query(1,pre[u],last[u])*(num[u]-num[p]);
                }
            }
            printf("%.6lf\n",(double)ans/fm[u]);
        }
    }
    return 0;

}
