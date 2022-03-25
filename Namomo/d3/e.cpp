#include<bits/stdc++.h> 
using namespace std;
namespace whywhy666{
	#define ms(a) memset(a,0,sizeof(a))
	#define pb push_back
	#define mp make_pair 
	#define lowbit(x) (x)&(-x)					  
	typedef long long ll;
	typedef pair<int,int> PII;
	const int INF=2e9;
	const ll INFF=4e18;
	const int maxn=1e6+5;
	const int pp=1e9+7;
	inline ll ceil_div(ll a,ll b){ return (a+b-1)/b; }
}
using namespace whywhy666;
inline int read()
{
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
const int base = 1e6 + 7;
int n;
vector<int>g[maxn];
ll anss=0;
map<ll,ll>ma;
ll dfs(int x,int fa){
	ll ans=1;
	for(int i=0;i<g[x].size();i++){
		if(g[x][i]==fa) continue;
		ans=(ans+dfs(g[x][i],x)*base % pp)%pp;
	}
	ma[ans % pp]++;
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].pb(v);
	}
	dfs(1,0);
	for(auto it=ma.begin();it!=ma.end();it++){
		ll tmp=it->second;
		anss+=(tmp)*(tmp-1)/2;
	}
	cout<<anss<<endl;
	return 0;
}
