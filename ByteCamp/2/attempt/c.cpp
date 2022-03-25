#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define ms(a,b) memset(a,b,sizeof(a))
#define msn(a,n,b) for(int i=0;i<=n;i++)a[i]=b
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define fi first
#define se second
using namespace std;
using namespace __gnu_pbds;
mt19937 rng_32(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
typedef double db;
const int mod=998244353;
const int seed=233;
const double PI=acos(-1.0);
const double eps=1e-7;
const int inf=0x3f3f3f3f;
const int max_n=100005;
ll ceil(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?(x+y-1)/y:-x/y;}
ll floor(ll x,ll y){if(x==0)return 0;if(y<0)x=-x,y=-y;bool sign=x>0;x=abs(x);return sign?x/y:-(x+y-1)/y;}
char str[max_n];
void rs(string& s){scanf(" %s",str);s=str;}
namespace {
    inline int Add(int x,int y){return (x+=y)>=mod?x-mod:x;}
    inline int Sub(int x,int y){return (x-=y)<0?x+mod:x;}
    inline int Mul(int x,int y) {return 1ll*x*y%mod;}
    inline int Pow(int x,int y=mod-2){int res=1;while(y){if(y&1)res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
/**********************head************************/
// struct HashTable{
//     static const int M=(1<<25)-1;
//     struct edge{
//         ll o;int w,next;
//     }G[2*M+1];
//     int h[M+1],tot;
//     void clear(){
//         tot=0;
//         memset(h,0,sizeof(h));
//     }
//     void add(ll x,int i){
//         G[++tot]={x,i,h[x&M]};
//         h[x&M]=tot;
//     }
//     int find(ll x){
//         for(int i=h[x&M];i;i=G[i].next){
//             if(G[i].o==x)return G[i].w;
//         }
//         return -1;
//     }
// }id;

gp_hash_table<ll, int> id;

int n,l,p;
char s[max_n];
//map<ll,int> dp,newdp;
int dp[5000000],newdp[5000000];
int mask=(1<<25)-1;
int tot;
ll val[5000000];
ll gval(int id){
    return val[id];
}
int gid(ll val){
  // return id.find(val);
  return id[val];
}
bool check(ll x){
    return __builtin_popcountll(x)<=p;
}
void init(){
    function<void(int,ll)> dfs=[&](int now,ll res){
        if(now==l){
            val[tot]=res;
            // id.add(res,tot);
            id[res] = tot;
            tot++;
            return;
        }
        res<<=1;
        if(check(res))dfs(now+1,res);
        if(check(res|1))dfs(now+1,res|1);
    };
    dfs(0,0);
}

int main(){
    scanf("%d%d%d",&n,&l,&p);
    init();
    scanf("%s",s+1);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<tot;j++)newdp[j]=0;
        for(int j=0;j<tot;j++){
            if(dp[j]==0)continue;
            ll x=gval(j);
            if(x>>(l-1)&1)x^=1ll<<(l-1);
            x<<=1;
            int nx;
            for(int k=0;k<2;k++){
                
                if(s[i]=='*'||s[i]-'0'==k){
                    if(check(x|k)){
                        nx=gid(x|k);
                        newdp[nx]=Add(newdp[nx],dp[j]);
                    }
                }
                
               /*
               if(check(x|k)){
                nx=gid(x|k);
                assert(nx>=0&&nx<tot);
                newdp[nx]=Add(newdp[nx],dp[j]);
               }
               */
              // for(auto p: dp) {
    //   if (p.second == 0) continue;
    //   ll x = p.fi;
    //   if (x >> (l - 1) & 1) x ^= 1ll << (l - 1);
    //   x <<= 1;
    //   for (int j = 0; j < 2; j++) {
    //     if (s[i] == '*' || s[i] - '0' == j) {
    //       if (check(x | j)) {
    //         newdp[x | j] = add(newdp[x | j], p.second);
    //       }
    //     }
    //   }
    // }
            }
        }
        for(int j=0;j<tot;j++)dp[j]=newdp[j];
    }
    int ans=0;
    for(int j=0;j<tot;j++)ans=Add(ans,dp[j]);
    printf("%d\n",ans);
    return 0;
}