#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll a[4],b[4];
ll ans[4];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        for(int i=1;i<=3;i++)scanf("%lld%lld",a+i,b+i);
        bool flag=false;
        for(int i=1;i<=3;i++)
        {
            for(int j=i+1;j<=3;j++)
            {
                ll r1=(a[i]*a[i]%4+4)%4,r2=(a[j]*a[j]%4+4)%4;
                //cout<<i<<' '<<j<<endl;
                //cout<<r1<<' '<<r2<<endl;
                if(r1!=r2)
                {
                    //cout<<r1<<' '<<r2<<endl;
                    ll k=4*b[j]-a[j]*a[j]-(4*b[i]-a[i]*a[i]);
                    ll x=(k+1)/2,y=(k-1)/2;
                    //cout<<k<<' '<<x<<' '<<y<<endl;
                    /*if((x-a[i])%2==0&&(y-a[j])%2==0)
                    {
                        flag=true;
                        ans[i]=(x-a[i])/2,ans[j]=(y-a[j])/2;

                        cout<<"ans: "<<ans[i]<<' '<<ans[j]<<endl;
                        break;
                    }*/
                    if((a[i]%2+2)%2==(x%2+2)%2)
                    {
                        flag=true;
                        ans[i]=(x-a[i])/2,ans[j]=(y-a[j])/2;
                       // cout<<"ans: "<<ans[i]<<' '<<ans[j]<<endl;
                        break;
                    }
                    else
                    {
                        flag=true;
                        ans[i]=(y-a[i])/2,ans[j]=(x-a[j])/2;
                        break;
                    }
                }
                else
                {
                    //cout<<r1<<' '<<r2<<endl;
                    ll k=4*b[j]-a[j]*a[j]-(4*b[i]-a[i]*a[i]);
                   // cout<<k<<endl;
                    //ll x=(k/2+2)/2,y=(k/2-2)/2;
                    //cout<<k<<' '<<x<<' '<<y<<endl;
                    for(int l=2;l<=sqrt(abs(k));l++)
                    {
                        if(abs(k)%l==0&&l%2==abs(k)/l%2)
                        {
                            ll x=(k/l+l)/2,y=(k/l-l)/2;
                            //cout<<l<<' '<<k/l<<' '<<x<<' '<<y<<endl;
                            //cout<<"kkkk"<<endl;
                            if((x-a[i])%2==0&&(y-a[j])%2==0)
                            {
                                flag=true;
                                ans[i]=(x-a[i])/2,ans[j]=(y-a[j])/2;
                                //cout<<"ans: "<<ans[i]<<' '<<ans[j]<<endl;
                                break;
                            }
                        }
                    }
                }
                //cout<<"ffffff"<<endl;
            }
            if(flag)break;
        }
        printf("%lld %lld %lld\n",ans[1],ans[2],ans[3]);
    }
    return 0;
}
