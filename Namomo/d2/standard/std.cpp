#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=1e6+11;
typedef long long ll;
int n,l,r,m,a[maxn],b[maxn];
ll ans;
ll calc(int i,int j){
	return 1ll*(a[i]+a[j])*(j-i);
}
void solve(int l,int r,int L,int R){
    if (l>r) return;
    int mid=(l+r)>>1;
    int pos=L;
    for (int i=L+1;i<=R;i++) if (calc(b[mid],pos)<calc(b[mid],i)) pos=i;
    ans=max(ans,calc(b[mid],pos));
    solve(l,mid-1,L,pos);
    solve(mid+1,r,pos,R);
}
 
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	int mx=-1;
	for (int i=1;i<n;i++) if (mx<a[i]) mx=a[i],b[++m]=i;
	solve(1,m,1,n);
	printf("%lld\n",ans);
	return 0;
}