#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n=2000005;
const int mod=1e9+7;
int T;
int n,p[max_n],d[max_n];
void getp(){
    int seed,a,b,mod;scanf("%d%d%d%d",&seed,&a,&b,&mod);
    for(int i=0;i<n;i++)p[i]=i;
    for(int i=1;i<n;i++){
        swap(p[i],p[seed%(i+1)]);
        seed=(1ll*seed*a+b)%mod;
    }
}
void getd(){
    int seed,a,b,mod;scanf("%d%d%d%d",&seed,&a,&b,&mod);
    for(int i=0;i<n;i++){
        d[i]=seed%10;
        seed=(1ll*seed*a+b)%mod;
    }
}
const int inf=0x3f3f3f3f;
const int max_log=21;
struct ST{
  int n,a[max_n];
  int st[max_log + 1][max_n];
  void init(int* _a,int _n){
    n=_n;
    for(int i=1;i<=n;i++)a[i]=_a[i];
    for(int i=1;i<=n;i++)st[0][i]=a[i];
    for(int j=1;j<=max_log;j++){
      for(int i=1;i+(1<<j)-1<=n;i++){
        st[j][i]=min(st[j - 1][i],st[j - 1][i+(1<<j-1)]);
      }
    }
  }
  int query(int l,int r){
    if(l>r)return inf;
    int i=__lg(r - l + 1);
    return min(st[i][l],st[i][r-(1<<i)+1]);
  }
}Tree;
int s[max_n];
int a[max_n];
int r[max_n];
int rk[max_n];
int now[max_n];
int main(){
  now[0] = 1;
  for (int i = 1; i < max_n; i++) {
    now[i] = 1ll * now[i - 1] * 10000019 % mod;
  }
  scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    for(int i=0;i<n;i++)s[i]=i%10;
    getp();
    getd();
    for(int i=0;i<n;i++){
      int x=p[i];
      if(s[x]!=d[i])a[i+1]=x;
      else a[i+1]=inf;
      s[x]=d[i];
    }
    Tree.init(a,n);
    for(int i=0;i<=n;i++)r[i]=i;
    auto cmp=[&](int x,int y){
      int a=x,b=y;
      if(a>b)swap(a,b);
      int pos=Tree.query(a+1,b);
      if(pos==inf)return x<y;
      else{
        bool res=(pos%10)<s[pos];
        res^=x>y;
        return res;
      }
    };
    sort(r,r+n+1,cmp);
    for(int i=0;i<=n;i++)rk[r[i]]=i;
    ll ans=0;
    for(int i=0;i<=n;i++){
      ans=(ans+1ll*rk[i]*now[i])%mod;
    }
    printf("%lld\n",ans);
  }
  return 0;
}