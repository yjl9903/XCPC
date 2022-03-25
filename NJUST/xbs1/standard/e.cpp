#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#define rep(i,j,k) for(register int i=j;i<=k;i++)
#define rrep(i,j,k) for(register int i=j;i>=k;i--)
#define erep(i,u) for(register int i=head[u];~i;i=nxt[i])
#define iin(a) scanf("%d",&a)
#define lin(a) scanf("%lld",&a)
#define din(a) scanf("%lf",&a)
#define s0(a) scanf("%s",a)
#define s1(a) scanf("%s",a+1)
#define print(a) printf("%lld",(ll)a)
#define enter putchar('\n')
#define blank putchar(' ')
#define println(a) printf("%lld\n",(ll)a)
#define IOS ios::sync_with_stdio(0)
using namespace std;
const int MAXN = 1e4+11;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-7;
typedef long long ll;
ll read(){
    ll x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll a[MAXN];
struct LB{
    ll b[33];
    void clear(){
        rep(i,0,31) b[i]=0;
    }
    void insert(int x){
        rrep(i,31,0) if(x>>i&1){
            if(b[i]) x^=b[i];
            else{
                b[i]=x;
                //rrep(j,i-1,0) if(b[j]&&(b[i]>>j&1)) b[i]^=b[j]; 
                //rep(j,i+1,30) if(b[j]>>i&1) b[j]^=b[i];
                break;
            }
        }
    }
    ll rnk1(){
        ll res=0;
        rrep(i,31,0) res=max(res,res^b[i]);
        return res;
    }
};
ll best;
struct ST{
    LB b[MAXN<<2],ans;
    #define lc o<<1
    #define rc o<<1|1
    void merge(LB &x,LB &y){
        rep(i,0,31) if(y.b[i]) x.insert(y.b[i]);
    }
    void pu(int o){
        merge(b[o],b[lc]);
        merge(b[o],b[rc]);
    }
    void init(){memset(b,0,sizeof b);}
    void build(int o,int l,int r){
        if(l==r){
            if(a[l]&best) b[o].insert(a[l]&best);
            return;
        }
        int mid=l+r>>1;
        build(lc,l,mid);
        build(rc,mid+1,r);
        pu(o);
    }
    void query(int o,int l,int r,int L,int R){
        if(L<=l&&r<=R){
            merge(ans,b[o]);
            return;
        }
        int mid=l+r>>1;
        if(L<=mid) query(lc,l,mid,L,R);
        if(R>mid)  query(rc,mid+1,r,L,R);
    }
}st;
int main(){
    int T=read();
    while(T--){
        int n=read();
        int q=read();
        ll k=read();
        best=0;
        rep(i,0,31) if(!(k>>i&1)) best|=(1ll<<i);
        rep(i,1,n) a[i]=read();
        st.init();
        st.build(1,1,n);
        rep(i,1,q){
            int L=read();
            int R=read();
            st.ans.clear();
            st.query(1,1,n,L,R);
            println(st.ans.rnk1()|k);
        }
    }
    return 0;
}