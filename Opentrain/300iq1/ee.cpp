#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef XLor
  #include <iostream>
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a) for(int i=lst[a];i;i=nxt[i])
#define pb(a) push_back(a)
using namespace std;

typedef long long ll;

const int N=6e3+5,Mo=998244353;

int pwr(int x,int y) {
	int z=1;
	for(;y;y>>=1,x=(ll)x*x%Mo)
		if (y&1) z=(ll)z*x%Mo;
	return z;
}

vector<int> to[N];
void add(int x,int y) {to[x].pb(y);}

int n,m,ty,deg[N],f[N],g[N],p[N],q[N],inv[N],x,y;
vector<int> h;

void inc(int &x,int y) {x=x+y>=Mo?x+y-Mo:x+y;}

namespace BM{
	vector<int> h[N];
	int cnt,fail[N],d[N],mx;
	vector<int> work(int n,int *a) {
		h[cnt=mx=0].clear();
		fo(i,1,n) {
			int now=-a[i];
			for(unsigned j=0;j<h[cnt].size();j++) (now+=(ll)a[i-j-1]*h[cnt][j]%Mo)%=Mo;
			d[i]=now;if (!now) continue;
			fail[cnt]=i;
			if (!cnt) {
				h[++cnt].clear();
				h[cnt].resize(i);
				continue;
			}
			vector<int> r;r.resize(i-fail[mx]-1);
			int mul=-(ll)now*pwr(d[fail[mx]],Mo-2)%Mo;
			r.pb(-mul);for(unsigned j=0;j<h[mx].size();j++) r.pb((ll)h[mx][j]*mul%Mo);
			if (r.size()<h[cnt].size()) r.resize(h[cnt].size());
			for(unsigned j=0;j<h[cnt].size();j++) (r[j]+=h[cnt][j])%=Mo;
			if (i-fail[mx]+h[mx].size()>=h[cnt].size()) mx=cnt;
			h[++cnt]=r;
		}
		return h[cnt];
	}
}

int main() {
	scanf("%d",&n);
	fo(i,1,n) deg[i]=0,to[i].clear();
	fo(i,1,n) scanf("%d%d",&x,&y);
	scanf("%d",&m);
	fo(i,1,m) {
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		deg[x]++;deg[y]++;
	}
	fo(i,1,n) inv[i]=pwr(deg[i],Mo-2);
	fo(i,1,n) f[i]=0;f[1]=1;p[0]=0;
	fo(i,1,n*2) {
		memset(g+1,0,n*4);
		fo(j,1,n) {
			int now=(ll)f[j]*inv[j]%Mo;
			for(int k:to[j]) inc(g[k],now);
		}
		memcpy(f+1,g+1,n*4);
		p[i]=f[n];f[n]=0;
	}
	h=BM::work(n*2,p);
	int m=h.size();
	fo(i,1,n*2) q[i]=0;
	fo(i,0,m-1) fo(j,0,m-i-1) (q[i+j+1]+=(ll)p[i]*h[j]%Mo)%=Mo;
	fo(i,1,m) q[i]=(p[i]-q[i])%Mo;
	int a=0,da=0,b=1,db=0;
	fo(i,1,m) {
		(a+=q[i])%=Mo,(da+=(ll)q[i]*i%Mo)%=Mo;
		(b-=h[i-1])%=Mo,(db-=(ll)h[i-1]*i%Mo)%=Mo;
	}
	int ans=((ll)da*b%Mo-(ll)db*a%Mo)%Mo;
	dbg((ans % Mo + Mo) % Mo, 1ll * b * b % Mo);
	ans=(ll)ans*pwr((ll)b*b%Mo,Mo-2)%Mo;
	printf("%d\n",(ans+Mo)%Mo);
	return 0;
}