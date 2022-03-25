#include<bits/stdc++.h>
using namespace std;
const int N=50005;
int p[N],k[N],ans[N],tmp[N];
int t,n,cnt;

int dp[N];
bool vis[N];

int calc(int n){
	for(int i=1; i<=n; i++){
		vis[k[i]]=1;
	}
	cnt=0;
	for(int i=1; i<=::n; i++){
		if(vis[i]){
			tmp[++cnt]=p[i];
			vis[i]=0;
		}
	}
	assert(cnt==n);
	for(int i=0; i<=n; i++) dp[i]=N;
	int res = 0;
	for (int i = 1; i <= n; i++){
		int p = lower_bound(dp + 1, dp + 1 + res, tmp[i]) - dp;
		dp[p] = tmp[i];
		res = max(p, res);
	}
	return res;
}

void gao(int l, int r){
	if(l>r) return;
	if(ans[l-1]==ans[r+1]){
		for(int i=l; i<=r; i++) ans[i]=ans[l-1];
		return;
	}
	int mid=(l+r)/2;
	ans[mid]=calc(mid);
	gao(l,mid-1);
	gao(mid+1,r);
	return;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&p[i]);
		}
		for(int i=1; i<=n; i++){
			scanf("%d",&k[i]);
		}
		ans[1]=1;
		ans[n]=calc(n);
		gao(2,n-1);
		for(int i=1; i<=n; i++){
			printf("%d%c",ans[i],i==n?'\n':' ');
		}
	}
	return 0;
}
