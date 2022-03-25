#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,c,d;
ll work(ll n)
{
    ll l=0,r=1e5;
    ll mid,ans;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(mid*(mid-1)/2<=n)ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
    ll t1=work(a),t2=work(d);
    if(b==0&&c==0)
    {
        if(t1==1&&t2==1)
        {
            printf("0");
            return 0;
        }
        else if(t1!=1)
        {
            if(t1*(t1-1)/2==a)
            {
                for(int i=0;i<t1;i++)printf("0");
                printf("\n");
                return 0;
            }
            else 
            {
                printf("impossible\n");
                return 0;
            }
        }
        else if(t2!=1)
        {
            if(t2*(t2-1)/2==d)
            {
                for(int i=0;i<t2;i++)printf("1");
                printf("\n");
                return 0;
            }
            else 
            {
                printf("impossible\n");
                return 0;
            }
        }
    }
    if(t1*(t1-1)/2!=a||t2*(t2-1)/2!=d||b+c!=t1*t2)printf("impossible\n");
    else
    {
        for(int i=0;i<b/t2;i++)printf("0"),t1--;
        b%=t2;
        for(int i=0;i<t2-b;i++)printf("1");
        if(t1)
        {
            printf("0");
            t1--;
        }
        for(int i=0;i<b;i++)printf("1");
        for(int i=0;i<t1;i++)printf("0");
        printf("\n");
    }
    return 0;
}