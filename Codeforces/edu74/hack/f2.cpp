#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=3e5+10;
const int M=1e5+10;
const int inf=1e9;
vector<int>g[N];
int T,n;
int cnt[N];
int dp[N];
int ans;
void dfs(int now,int fa){
	if(g[now].size()==1&&g[now][0]==fa){
		dp[now]=0;
		return;
	}
	int mx1=-1;
	int mx2=-1;
	for(int i=0;i<g[now].size();i++){
		if(g[now][i]==fa) continue;
		dfs(g[now][i],now);
		if(mx1<=dp[g[now][i]]){
			mx2=mx1;
			mx1=dp[g[now][i]];
		}
		else
		if(mx2<=dp[g[now][i]]){
			mx2=dp[g[now][i]];
		}
	}
	if(mx2!=-1) ans=max(ans,mx1+mx2+cnt[now]+2);
	else ans=max(ans,mx1+cnt[now]+2);
	dp[now]=mx1+cnt[now];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			g[i].clear();
			cnt[i]=0;
			dp[i]=0;
		}
		for(int i=1;i<n;i++){
			int a,b;
			scanf("%d %d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		for(int i=1;i<=n;i++){
			cnt[i]=g[i].size()-1;
			
		}
		ans=0;
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}