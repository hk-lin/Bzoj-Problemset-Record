#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1,sizeof(x))
#define INF 0x3f3f3f3f
#define mod 1000000007
#define LL long long
#define next nexted
using namespace std;
const int N=3e4+10;
const int type=2;
char s[N];
int n,m,T,tot;
int vis[N];
struct node
{
    int pre,tag,dep,next[type];
}trie[N];
void init()
{
    tot=0;
    clr(trie);
    clr(vis);
    return ;
}
int makenode()
{
    return ++tot;
}
void add(int root,char *s)
{
    int now=root,len=strlen(s),p;
    for(int i=0;i<len;i++)
    {
        p=s[i]-'0';
        if(!trie[now].next[p]) trie[now].next[p]=makenode();
        now=trie[now].next[p];
        trie[now].dep=i+1;
    }
    trie[now].tag=now;
    return ;
}
void build()
{
    queue<int> que;
    for(int i=0;i<type;i++)
        if(trie[0].next[i]) que.push(trie[0].next[i]);
    int now,nowto;
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for(int i=0;i<type;i++)
        {
            nowto=trie[now].next[i];
            if(nowto)
            {
                trie[nowto].pre=trie[trie[now].pre].next[i];
                que.push(nowto);
                if(trie[trie[nowto].pre].tag && !trie[nowto].tag)
                    trie[nowto].tag=trie[trie[nowto].pre].tag;
            }
            else
                trie[now].next[i]=trie[trie[now].pre].next[i];
        }
    }
    return ;
}
bool dfs(int now)
{
    if(trie[now].tag || vis[now]==2) return 0;
    if(vis[now]==1) return 1;
    vis[now]=1;
    bool inf=0;
    for(int i=0;i<type;i++)
        inf=(inf || dfs(trie[now].next[i]));
    vis[now]=2;
    return inf;
}
int main()
{
    scanf("%d",&n);
    init();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        add(0,s);
    }
    build();
    if(dfs(0))
        printf("TAK\n");
    else
        printf("NIE\n");
    return 0;
}
