#include<bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repp(i,a,b) for(ll i=a;i<=b;i++)
#define rep1(i,a,b) for(int i=a;i>=b;i--)
#define mem(gv) memset(gv,0,sizeof(gv))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define QAQ 0
#define miaojie
#ifdef miaojie
  #define dbg(args...) do {cout << #args << " : "; err(args);} while (0)
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#else
  #define dbg(...)
#endif

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pLL;
const int mod=1e9+7;
const int maxn=2e5+22;
const ll inf=1ll<<60;

struct node{
	ll v,r;
}a[maxn];
ll n,dp[maxn],pre[maxn],id[maxn],vis[maxn]; 

bool cmp(node x,node y){
	return x.v<y.v;
}

int main(){
	scanf("%lld",&n);
	repp(i,1,n){
		scanf("%lld",&a[i].v);
		a[i].r=i;
	}
	sort(a+1,a+1+n,cmp);
	repp(i,1,n){
		dp[i]=inf;
	}

	dp[3]=a[3].v-a[1].v;
	dp[4]=a[4].v-a[1].v;
	dp[5]=a[5].v-a[1].v;
	repp(i,4,n){
		repp(j,i-5,i-3){
			if(j<1) continue;
			ll tmp=dp[j]+a[i].v-a[j+1].v;
			if(tmp<dp[i]){
				dp[i]=tmp;
				pre[i]=j;
			}
		}
	}
	
	ll q=n,cnt=1,s=1;
	while(pre[q]){
		cnt++;
		q=pre[q];
		vis[q]=1;
	}
	repp(i,1,n){
		id[a[i].r]=s;
		s+=vis[i];	
	}
	
	printf("%lld %lld\n",dp[n],cnt);
	repp(i,1,n) printf("%lld ",id[i]);
	return QAQ;
}