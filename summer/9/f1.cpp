#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n=10005;
int T;
int a[max_n],n,m;
int cnt;
ll lcm(int a, int b){
    return 1ll * a / __gcd(a,b) * b;
}
ll sum(int x){
    return 1ll*x*(x+1)/2;
}
int main(){
    scanf("%d",&T);
    int cas=1;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",a+i),a[i]=__gcd(a[i],m);
        sort(a+1,a+n+1);
        int tot=unique(a+1,a+n+1)-a-1;
        cnt=0;
        for(int i=1;i<=tot;i++){
            bool f=true;
            for(int j=1;j<=cnt;j++)if(a[i]%a[j]==0){
                f=false;
                break;
            }
            if(f)a[++cnt]=a[i];
        }
        //for(int i=1;i<=cnt;i++)cout<<a[i]<<' ';
        //cout<<endl;
        assert(1 <= cnt);
        ll ans=0;
        for(int i=1;i<(1<<cnt);i++){
            ll x = 1;
            int c = 0;
            for(int j=0;j<cnt;j++){
                if(i >> j & 1) x = lcm(x,a[j+1]),c++;
            }
            if(c&1)ans+=x*sum(m/x)-m;
            else ans-=x*sum(m/x)-m;
        }
        printf("Case #%d: %lld\n",cas++,ans);
    }
    return 0;
}