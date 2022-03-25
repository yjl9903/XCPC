//by yjz
#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
typedef long long ll;
const int mod=998244353;
typedef long long ll;
const int hs_mod = 1e9+9;
const int hs_base = 233333;
const int maxn = 200111;
int hs[maxn], pwb[maxn], n;
char s[maxn];
int query_hash(int l, int r)
{
	int tmp = (hs[r]-1ll*hs[l-1]*pwb[r-l+1])%hs_mod;
	if (tmp<0) tmp += hs_mod;
	return tmp;
}
int get_lcp(int x, int y)
{
	if (s[x]!=s[y]) return 0;
	int l = 1, r = n-max(x,y)+1;
	while (l<=r)
	{
		int mid = l+r>>1;
		if (query_hash(x, x+mid-1)==query_hash(y, y+mid-1)) l = mid+1;
		else r = mid-1;
	}
	return r;
}
int get_rlcp(int x, int y)
{
	if (s[x]!=s[y]) return 0;
	int l = 1, r = min(x,y);
	while (l<=r)
	{
		int mid = l+r>>1;
		if (query_hash(x-mid+1, x)==query_hash(y-mid+1, y)) l = mid+1;
		else r = mid-1;
	}
	return r;
}
bool compare(int x, int y)
{
    // dbg(x, y);
	int len = get_lcp(x, y);
	if (x+len>n) return false;
	if (y+len>n) return true;
	return s[x+len]<s[y+len];
}
vector<int> vr[maxn];
const int maxr = maxn*12;
int rv[maxr], rp[maxr], rtot;
int dp[maxn];
unordered_map<ll,int> mp_runs;
void add_runs(int l, int r, int p)
{
	if (mp_runs.find(1ll*l*n+r)!=mp_runs.end()) return;
    // dbg(l, r, p);
	mp_runs[1ll*l*n+r] = 1;
	for (int i=0; i<p*2&&l+2*p-1+i<=r; i++)
	{
		rtot++;
		rp[rtot] = p*2;
		for (int j=l+2*p-1+i; j<=r; j+=2*p)
		{
            dbg(j, p * 2);
			vr[j].PB(rtot);
		}
	}
}
void check_runs(int l, int r)
{
    // dbg(l, r);
	int L = r-l;
	int l1 = get_lcp(l, r);
	int l0 = get_rlcp(l-1, r-1);
    //dbg(l, r, l1, l0);
	if (l0+l1>=L)
	{
		add_runs(l-l0, r+l1-1, L);
	}
}
void compute_runs(int type)
{
	static int st[maxn], stn;
	stn = 0; st[stn++] = n+1;
	for (int i=n; i>=1; i--)
	{
		while (stn>1 && compare(i, st[stn-1])==type) stn--;
		check_runs(i, st[stn-1]);
		st[stn++] = i;
	}
}
void upd(int &x, int v) {x = x+v>=mod?x+v-mod:x+v;}
void solve()
{
	memset(rv, 0, sizeof(rv));
	int sum = 1;
	dp[0] = 1;
	for (int i=1; i<=n; i++)
	{
		dp[i] = sum;
		int csum = 0;
		for (int j=0; j<vr[i].size(); j++)
		{
			int &id = vr[i][j];
			upd(rv[id], dp[i-rp[id]]);
			upd(csum, rv[id]);
		}
		csum = ((-2*csum)%mod+mod)%mod;
		upd(dp[i], csum);
		upd(sum, dp[i]);
	}
}
int main()
{
	pwb[0] = 1;
	for (int i=1; i<maxn; i++) pwb[i] = 1ll*pwb[i-1]*hs_base%hs_mod;
	scanf("%s", s+1);
	n = strlen(s+1);
	for (int i=1; i<=n; i++) hs[i] = (1ll*hs[i-1]*hs_base+s[i])%hs_mod;
	compute_runs(0);
	compute_runs(1);
	solve();
	cout<<dp[n]<<endl;
    return 0;
}