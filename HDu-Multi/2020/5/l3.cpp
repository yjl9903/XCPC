#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
namespace {
    inline int Add(int x,int y){return (x+=y)>=mod?x-mod:x;}
    inline int Sub(int x,int y){return (x-=y)<0?x+mod:x;}
    inline int Mul(int x,int y) {return 1ll*x*y%mod;}
    inline int Pow(int x,int y=mod-2){int res=1;while(y){if(y&1)res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
const int max_n=5005;
int dp[max_n][max_n];
int sum[max_n][max_n];
int f[max_n];
int inv[max_n];
void init(int n){
    f[0]=1;
    for(int i=1;i<=n;i++)f[i]=Mul(f[i-1],i);
    inv[n]=Pow(f[n],mod-2);
    for(int i=n-1;i>=0;i--)inv[i]=Mul(inv[i+1],i+1);
}
int A(int n,int m){
    if(m<0||n<m)return 0;
    return 1ll*f[n]*inv[n-m]%mod;
}
int C(int n,int m){
    if(m<0||n<m)return 0;
    return 1ll*f[n]*inv[n-m]%mod*inv[m]%mod;
}
int ans[max_n];
int T,n,k;
int main(){
    init(max_n-1);
    //cout<<C(3,1)<<endl;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        int m=n/(k+1);
        int r=n-m*(k+1);
        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++)dp[i][j]=0;
        }
        for(int i=1;i<=m;i++){
            if(i==1){
                int x=n-1+1-(m-1+1)-r-(m-1)*k;
                dp[1][1]=A(x,k);
                //cout<<dp[1][1]<<endl;
            }
            else{
                for(int j=1;j<=n;j++){
                    int x=n-j+1-(m-i+1)-r-(m-i)*k;
                    dp[i][j]=Mul(A(x,k),sum[i-1][j-1]);
                }
            }
            for(int j=1;j<=n;j++)sum[i][j]=Add(sum[i][j-1],dp[i][j]);
        }
        for(int i=1;i<=n;i++)ans[i]=0;
        for(int i=1;i<=n;i++){
            int x=dp[m][i];
            //cout<<i<<' '<<x<<endl;
            x=Mul(x,C(n-i-1,r-1));
            //cout<<n-i-1<<' '<<r-1<<' '<<C(n-i-1,r-1)<<endl;
            //cout<<i<<' '<<x<<endl;
            ans[i+1]=Add(ans[i+1],x);
            ans[n+1]=Sub(ans[n+1],x);
        }
        for(int i=1;i<=n;i++)ans[i]=Add(ans[i-1],ans[i]);
        int way=1;
        for(int i=1;i<=m;i++)way=Mul(way,A(n-(i-1)*(k+1)-1,k));
        way=Pow(way,mod-2);
        for(int i=1;i<=n;i++)ans[i]=Mul(ans[i],way);
        for(int i=1;i<=n;i++)printf("%d%c",ans[i],i==n?'\n':' ');
    }
}