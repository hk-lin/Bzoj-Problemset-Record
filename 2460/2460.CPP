#include<bits/stdc++.h>
#define clr(x) memset(x,0,sizeof(x))
#define clr_1(x) memset(x,-1.sizeof(x))
#define LL long long
#define mod 1000000007
using namespace std;
const int N=1e5+10;
int num;
struct Node
{
    LL val,num;
}good[N];
int n;
LL ans;
LL liner[65],p;
bool cmp(Node a,Node b)
{
    return a.val>b.val;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&good[i].num,&good[i].val);
    }
    sort(good+1,good+n+1,cmp);
    ans=0;
    clr(liner);
    for(int i=1;i<=n;i++)
    {
        p=good[i].num;
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
        if(p)
        {
            ans+=good[i].val;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
