#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
using namespace std;
const int N=3e5+10;
const int M=3e4+10;
const int type=26;
struct node
{
    int next[type];
    int tag;
}trie[N];
int tot,n,m,ans;
char s[M][310];
int stot;
int infer[M];
int net[type+10][type+10];
void add(char *s,int odr)
{
    int now=0;
    int len=strlen(s),p;
    for(int i=0;i<len;i++)
    {
        p=s[i]-'a';
        if(!trie[now].next[p])
            trie[now].next[p]=++tot;
        now=trie[now].next[p];
    }
    trie[now].tag=odr;
    return;
}
int vis[type+10];
void init()
{
    tot=0;
    clr(trie);
    stot=0;
    clr(infer);
    clr(net);
    return ;
}
void addedge(int u,int v)
{
    net[u][v]++;
    return ;
}
void deledge(int u,int v)
{
    --net[u][v];
    return ;
}
bool dfs(int u)
{
    vis[u]=1;
    int p;
    for(int i=0;i<type;i++)
    if(net[u][i])
    {
        if(vis[i]==1)
            return true;
        if(vis[i]==2)
            continue;
        if(dfs(i))
            return true;
    }
    vis[u]=2;
    return false;
}
void dfs(int now,int dep)
{
    if(trie[now].tag)
    {
        int flag=0;
        clr(vis);
        for(int i=0;i<type;i++)
        {
            if(!vis[i] && dfs(i))
            {
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            stot++;
            infer[trie[now].tag]=1;
        }
        return ;
    }
    for(int i=0;i<type;i++)
        if(trie[now].next[i])
        {
            for(int j=0;j<type;j++)
                if(trie[now].next[j] && i!=j)
                    addedge(j,i);
            dfs(trie[now].next[i],dep+1);
            for(int j=type-1;j>=0;j--)
                if(trie[now].next[j] && i!=j)
                    deledge(j,i);
        }
    return ;
}
int main()
{
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s[i]);
        add(s[i],i);
    }
    stot=0;
    dfs(0,0);
    printf("%d\n",stot);
    for(int i=1;i<=n;i++)
        if(infer[i])
            printf("%s\n",s[i]);
    return 0;
}
