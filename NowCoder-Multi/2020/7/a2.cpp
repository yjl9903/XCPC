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
#define sq(x) ((x)*(x))
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
const ll mod=1e9+7;
const int maxn=2e5+22;

int cnt,n,r,ans=0,tp;
vector<pii>v;
vector<pii>tmp;
int dist[300][300];
bool vis[200];

void gkd(int c){
	if(c==tp+1){
		int dis=0,tpsiz=(int)tmp.size();
		for(int i=0;i<tpsiz;i++){
			for(int j=i+1;j<tpsiz;j++){
				pii p1=tmp[i], p2=tmp[j];
			//	dbg(i,j,p1.fi,p1.se,p2.fi,p2.se);
				dis=dis+sq(p1.first-p2.first)+sq(p1.second-p2.second);
			}
		//	dbg(dis);	
		}
		ans=max(ans,dis);
		return;
	}
	int siz=v.size();
	for(int i=0;i<siz;i++){
		tmp.pb(v[i]);

		if(n==3||n==5||n==7||n==6){
			int tx=-v[i].fi,ty=v[i].se;
			tmp.pb(pii{tx,ty}); gkd(c+1); tmp.pop_back();
			repp(j,-2,2){
				repp(k,-2,2){
					if(j==0 && k==0) continue;
					int dd=sq(tx+j)+sq(ty+k),jd=sq(r);
					if(dd<=jd) {tmp.pb(pii{tx+j,ty+k}); gkd(c+1); tmp.pop_back();}
				}
			}
		}
		else if(n==8){
			tmp.pb(pii{-v[i].fi,v[i].se});
			tmp.pb(pii{-v[i].fi,-v[i].se});
			tmp.pb(pii{v[i].fi,-v[i].se});
			gkd(c+1);
			tmp.pop_back();
			tmp.pop_back();
			tmp.pop_back();			
		}
		tmp.pop_back();
	}
}

int main(){
	for(n=7;n<=8;n++){
		for(r=30;r>=1;r--){
			ans=0; mem(vis);
			v.clear(); tmp.clear();
			if(n==1||n==2||n==4) continue;
			if(n==3||n==5||n==7){
				tmp.pb(pii{0,r});
				tp=n/2;
				repp(i,0,r){
					repp(j,-r,r){
						int d=sq(i)+sq(j), jd=sq(r);
						if(d>jd) continue;
						int d1=sq(i+1)+sq(j), d2=sq(i-1)+sq(j), d3=sq(i)+sq(j+1)
						,d4=sq(i)+sq(j-1);
						if(d1>jd||d2>jd||d3>jd||d4>jd){
							v.push_back(pii(i,j));
						}												
					}
				}
				gkd(1);
			}
			
			if(n==6){
				tmp.pb(pii{0,r}); tmp.pb(pii{0,-r});
				tp=2;
				repp(i,0,r){
					repp(j,-r,r){
						int d=sq(i)+sq(j), jd=sq(r);
						if(d>jd) continue;
						int d1=sq(i+1)+sq(j), d2=sq(i-1)+sq(j), d3=sq(i)+sq(j+1)
						,d4=sq(i)+sq(j-1);
						if(d1>jd||d2>jd||d3>jd||d4>jd){
							v.push_back(pii(i,j));
						}
					}
				}
				gkd(1);
			}
			if(n==8){
				tmp.pb(pii{0,r}); tmp.pb(pii{0,-r});
				tmp.pb(pii{r,0}); tmp.pb(pii{-r,0});
				tp=1;
				repp(i,0,r){
					repp(j,0,r){
						int d=sq(i)+sq(j), jd=sq(r);
						if(d>jd) continue;
						int d1=sq(i+1)+sq(j), d2=sq(i-1)+sq(j), d3=sq(i)+sq(j+1)
						,d4=sq(i)+sq(j-1);
						if(d1>jd||d2>jd||d3>jd||d4>jd){
							v.push_back(pii(i,j));
						}
					}
				}
				gkd(1);				
			}
			
			printf("%d %d %d\n",n,r,ans);
		}
	}
	return QAQ;
}
