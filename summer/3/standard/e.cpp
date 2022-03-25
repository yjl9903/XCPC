#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ll long long 
using namespace std;
struct node{
	int l,r;
	bool operator<(const struct node& rhs)const{
		return l<rhs.l;
	}
}t[100005];
int n,m,c[100005];
priority_queue<int,vector<int>,greater<int> >q;
int solve(){
	while(!q.empty())q.pop();
	int j=0;
	int ans=-1;
	for(int i=0;i<m;i++){
		while(j<n&&t[j].l<=c[i])q.push(t[j].r),j++;
		while(!q.empty()&&q.top()<c[i])q.pop();
		if(q.empty())return -1;
        dbg(q.size());
		ans=max(ans,n-(int)q.size()+1);
		q.pop();
	}
	return ans;
}

int main(){
	int T;cin>>T;
	int kcase=0;
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)scanf("%d%d",&t[i].l,&t[i].r);
		for(int i=0;i<m;i++)scanf("%d",&c[i]);
		
		sort(t,t+n);
		sort(c,c+m);
		
		int ans=solve();
		if(ans==-1)printf("Case #%d: IMPOSSIBLE!\n",++kcase);
		else printf("Case #%d: %d\n",++kcase,ans);
	}
		
	return 0;
}