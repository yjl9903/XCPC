#include <bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
typedef pair <int,int> pii;
const int N=1e6+50, L=21, mod=998244353;
inline int add(int x,int y) {return (x+y>=mod) ? (x+y-mod) : (x+y);}
inline int dec(int x,int y) {return (x-y<0) ? (x-y+mod) : (x-y);}
inline void up(int &x,int y) {x=add(x,y);}
inline void dn(int &x,int y) {x=dec(x,y);}

int n,lg[N]; char s[N];
struct SA {
	int sa[N],a[N],b[N],c[N],*rk=a,*sa2=b,m,h[L][N];
	inline void Rsort() {
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) ++c[rk[i]];
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[rk[sa2[i]]]--]=sa2[i];	
	}
	inline void init() {
		for(int i=1;i<=n;i++) sa2[i]=i, rk[i]=s[i]-'a'+1;
		m=26; Rsort();
		for(int w=1;w<=n;w<<=1) {
			int p=0;
			for(int i=n-w+1;i<=n;i++) sa2[++p]=i;
			for(int i=1;i<=n;i++) if(sa[i]>w) sa2[++p]=sa[i]-w;
			Rsort(); swap(rk,sa2); rk[sa[1]]=p=1;
			for(int i=2;i<=n;i++)
				rk[sa[i]]=(sa2[sa[i]]==sa2[sa[i-1]] && sa2[sa[i]+w]==sa2[sa[i-1]+w]) ? p : ++p;
			m=p; p=0; if(m==n) break;
		}
		for(int i=1,k=0,j;i<=n;h[0][rk[i++]]=k)
			for(k?k--:k,j=sa[rk[i]-1];s[i+k]==s[j+k];++k);
		for(int i=1;i<L;i++)
			for(int j=1;j+(1<<i)-1<=n;++j)
				h[i][j]=min(h[i-1][j],h[i-1][j+(1<<(i-1))]);
	}
	inline int ask(int x,int y) {
		x=rk[x], y=rk[y]; 
		if(x>y) swap(x,y);
		++x; int l=lg[y-x+1];
		return min(h[l][x],h[l][y-(1<<l)+1]);
	}
} ori,rev; 

const int T=2e7+50;
int tot,cov[T],si[N];
int f[N],prd[T][2];
vector <pii> g[N];
int main() {
	scanf("%s",s+1); n=strlen(s+1);
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	ori.init();
	reverse(s+1,s+n+1);
	rev.init();
	
	for(int i=1;i<=n;i++) si[i]=si[i-1]+n/i;
	for(int i=1;i<=n;i++) {
		int l=0, r=0;
		for(int j=i;j+i<=n;j+=i) if(j>r) {
			int L=rev.ask(n-j+1,n-(j+i)+1), R=ori.ask(j,j+i);
			l=j-L+1, r=j+R-1;
			if(r-l+1<i) continue;
			if(cov[si[i-1]+j/i]) continue;
			for(int x=i+i;l+x+x-1<=r+i;x+=i)
				cov[si[x-1]+(l+x-1)/x]=1;
			int last=tot+1;
			for(int k=l;k<=r-i+1;k++) {
				if(k<l+i) ++tot;
				g[k+2*i-1].push_back(pii(i,(k-l)%i+last));
			}
		}
	}
	
	int ans; f[0]=ans=1;
	for(int i=1;i<=n;i++) {
        dbg(i);
		f[i]=ans;
		for(auto v:g[i]) {
            dbg(v.first, v.second);
			int x=v.second, l=v.first;
			up(prd[x][(i/l)&1],f[i-2*l]);
			dn(f[i],prd[x][(i/l)&1]*2%mod);
		} ans=add(ans,f[i]);
	} cout<<f[n]<<'\n';
}