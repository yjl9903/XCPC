#include<bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define inf 0x3f3f3f3f
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repp(i,a,b) for(int i=a;i<=b;i++)
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

int T,m[30][30],d[30];
bool vis[30],f;
char s[maxn];
vector<char>ans;

void dfs1(int x,int fa){
	if(f) return;
	vis[x]=1;
	repp(i,0,25){
		if(i==fa || i==x) continue;
		if(m[x][i]){
			if(vis[i]){
				f=1;
				return;
			}
			dfs1(i,x);
		}
	}
}

void dfs2(int x,int fa){
	if(f) return;
	vis[x]=1;
	ans.pb((char)(x+'a'));
	repp(i,0,25){
		if(i==fa || i==x) continue;
		if(m[x][i] && !vis[i]){
			dfs2(i,x);
		}
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);
		int l=strlen(s+1);
		f=0;
		mem(m); mem(d); mem(vis); ans.clear();
		
		repp(i,1,l-1){
			if(!m[s[i]-'a'][s[i+1]-'a']){
				m[s[i]-'a'][s[i+1]-'a']=1;
				m[s[i+1]-'a'][s[i]-'a']=1;
				d[s[i]-'a']++;
				d[s[i+1]-'a']++;
			}
		}
		repp(i,0,25){
			if(d[i]>=3){
				f=1;
				break;
			}
		}
		if(f) puts("NO");
		else{
			repp(i,0,25){
				if(!vis[i]) dfs1(i,-1);
			}
			mem(vis);
			
			repp(i,0,25){
				if(!vis[i] && d[i]<=1) dfs2(i,-1);
			}
			
			if(f) puts("NO");
			else{
				puts("YES");
				for(auto x:ans) printf("%c",x);
				printf("\n");
			}	
		}
	}
	return QAQ;
}
