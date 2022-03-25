#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define rep(i,a,n) for (int i=a;i<=n;i++)
#define per(i,a,n) for (int i=n;i>=a;i--)
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int,int> pii;
ll qpow(ll a,ll b){ll ans=1;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)ans=ans*a%mod;a=a*a%mod;}return ans;}
ll gcd(ll a,ll b){return b>0?gcd(b,a%b):a;}
int n,m,T,N;
int lz[maxn<<2];
struct node{
	ll mi,si,cnt,l,r,len;
	ll val,val1;
	node(){
		mi=si=cnt=l=r=val=len=val1=0;
	}
	void Max(const ll& C){
		if(C<=mi) return;
		l=max(l,C);
		r=max(r,C);
		val-=1ll*cnt*(C-mi);
		// cout << "Delta: " << C << " " << mi << " " << 1ll*cnt*(C-mi) << endl;
		mi=C;
	}
}tr[maxn<<2];
vi v;
#define lson rt<<1
#define rson rt<<1|1
void pushup(const int& rt){
	tr[rt].cnt=0;
	tr[rt].l=tr[lson].l;
	tr[rt].r=tr[rson].r;
	tr[rt].val=tr[lson].val+tr[rson].val;
	tr[rt].mi=min(tr[lson].mi,tr[rson].mi);
	tr[rt].si=min(tr[lson].si,tr[rson].si);
	if(tr[lson].mi^tr[rson].mi) tr[rt].si=min(tr[rt].si,max(tr[lson].mi,tr[rson].mi));
	if(tr[rt].mi==tr[lson].mi) tr[rt].cnt+=tr[lson].cnt;
	if(tr[rt].mi==tr[rson].mi) tr[rt].cnt+=tr[rson].cnt;
	if(tr[lson].r+tr[rson].l!=2ll*tr[rt].mi&&(tr[lson].r==tr[rt].mi||tr[rson].l==tr[rt].mi)){
		tr[rt].cnt++;
	}
	tr[rt].val+=abs(tr[rson].l-tr[lson].r);
}
void pushdown(const int& rt){
	tr[lson].Max(tr[rt].mi);
	tr[rson].Max(tr[rt].mi);
}
void build(int l,int r,int rt){
	lz[rt]=0;
	tr[rt]=node();
	if(l==r){
		tr[rt]=node();
		tr[rt].si=INT_MAX;
		tr[rt].len=v[l]-v[l-1];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,lson);
	build(mid+1,r,rson);
	pushup(rt);
	tr[rt].len=tr[lson].len+tr[rson].len;
}
void update1(int L,int R,int l,int r,int rt){
	if(r<L||R<l) return;
	if(L<=l&&r<=R){
		lz[rt]=1;
		tr[rt].val1=tr[rt].len;
		return;
	}
	if(lz[rt]){
		lz[lson]=lz[rson]=1;
		tr[lson].val1=tr[lson].len;
		tr[rson].val1=tr[rson].len;
		lz[rt]=0;
	}
	int mid=l+r>>1;
	update1(L,R,l,mid,lson);
	update1(L,R,mid+1,r,rson);
	tr[rt].val1=tr[lson].val1+tr[rson].val1;
}
void update(ll C,int L,int R,int l,int r,int rt){
	if(r<L||R<l) return;
	if(C<=tr[rt].mi) return;
	if(L<=l&&r<=R&&tr[rt].si>C){
		tr[rt].Max(C);
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	update(C,L,R,l,mid,lson);
	update(C,L,R,mid+1,r,rson);
	pushup(rt);
}
void dfs(int l, int r, int rt) {
	if (l == r) {
		cout << tr[rt].mi << " ";
		return ;
	}
	pushdown(rt);
	int mid=l+r>>1;
	dfs(l,mid,rt << 1);
	dfs(mid + 1, r, rt << 1 | 1);
}
struct Question{
	int l,r,h;
}q[maxn];
int getId(int x){
	return lower_bound(all(v),x)-v.begin()+1;
}
int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);	
		v.clear();
		for(int ql,qr,qh,i=1;i<=n;i++){
			scanf("%d%d%d",&ql,&qr,&qh);
			q[i]={ql,qr,qh};  
			v.pb(ql);
			v.pb(qr);
		}
		v.pb(0);
		v.pb(1e9);
		sort(all(v));
		v.erase(unique(all(v)),v.end());
		N=v.size();
		build(1,N,1);
		for(int ql,qr,i=1;i<=n;i++){
			ql=getId(q[i].l);
			qr=getId(q[i].r);
			update1(ql,qr-1,1,N,1);
			update(q[i].h,ql,qr-1,1,N,1);
			printf("%lld %lld\n",tr[1].val+2ll*tr[1].val1, tr[1].val);
			if (i == 21) {
				dfs(1, N, 1);
				cout << endl;
			}
		}
	}
	return 0;
}