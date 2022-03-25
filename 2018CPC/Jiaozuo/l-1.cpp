#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
struct mat
{
    int n,m;
    ll a[9][9];
    mat operator * (mat b)
    {
        mat c;
        c.n=n;
        c.m=b.m;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<b.m;j++)
            {
                c.a[i][j]=0;
                for(int k=0;k<m;k++)
                {
                    (c.a[i][j]+=a[i][k]*b.a[k][j])%=mod;
                }
            }
        }
        return c;
    }
    void operator = (mat b)
    {
        n=b.n;
        m=b.m;
        for(int i=0;i<b.n;i++)
        {
            for(int j=0;j<b.m;j++)a[i][j]=b.a[i][j];
        }
    }
};
mat quick_pow(mat a,ll n)
{
        mat c;
        c.n=a.n;
        c.m=a.m;
        for(int i=0;i<c.n;i++)
        {
            for(int j=0;j<c.m;j++)c.a[i][j]=(i==j);
        }
        while(n)
        {
            if(n&1)c=c*a;
            a=a*a;
            n>>=1;
        }
        return c;
}
int T;
int n;
mat A,s,t;
int main()
{
    scanf("%d",&T);
    A.n=A.m=9;
    s.n=9,s.m=1;
    for(int i=0;i<9;i++)s.a[i][0]=1;
    A.a[0][1]=A.a[0][2]=1;
    A.a[1][4]=A.a[1][5]=1;
    A.a[2][7]=A.a[2][8]=1;
    A.a[3][0]=A.a[3][1]=1;
    A.a[4][3]=A.a[4][5]=1;
    A.a[5][6]=A.a[5][7]=A.a[5][8]=1;
    A.a[6][0]=A.a[6][2]=1;
    A.a[7][3]=A.a[7][4]=A.a[7][5]=1;
    A.a[8][6]=A.a[8][7]=1;
    while(T--)
    {
        scanf("%lld",&n);
        if(n==1)printf("3\n");
        else if(n==2)printf("9\n");
        else
        {
            t=quick_pow(A,n-2)*s;
            ll ans=0;
            for(int i=0;i<9;i++)ans=(ans+t.a[i][0])%mod;
            printf("%lld\n",ans);
        }
    }
    return 0;
}