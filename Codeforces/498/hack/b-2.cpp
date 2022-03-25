#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

struct d
{
    int v,id;
}a[2005];

bool cmp(d x, d y)
{
    return x.v>y.v;
}

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].v);
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    int b[2005]={0},cnt=0,ans=0;
    for(int i=1;i<=k;i++)
    {
        b[cnt++]=a[i].id;
        ans+=a[i].v;
    }
    sort(b,b+cnt);
    b[cnt]=n+1;
    printf("%d\n",ans);
    for(int i=0;i<k;i++)
    {
        if(i==0)printf("%d",b[i+1]-1);
        else printf(" %d",b[i+1]-b[i]);
    }
    printf("\n");
    return 0;
}