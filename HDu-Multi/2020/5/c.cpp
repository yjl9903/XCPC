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
const ll mod=1e9+7;
const int maxn=5e5+22;

int T,n,k;
vector<int>ve[maxn],tmp[maxn]; 

int poww(int a,int b){
    int ans=1,base=a;
    while(b){
        if(b&1!=0)
            ans*=base;
        base*=base;
        b>>=1;
    }
    return ans;
} 

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        int sum=2*n*poww(2,k);
        int row=sum,col=1;
        repp(i,1,sum){
            ve[i].clear(); tmp[i].clear();
            ve[i].pb(i);
        }
        
        repp(r,1,k){
            repp(i,1,row/2){
                rep1(j,col-1,0){
                    tmp[row/2+1-i].pb(ve[i][j]);
                }
            }
            repp(i,row/2+1,row){
                repp(j,0,col-1){
                    tmp[i-row/2].pb(ve[i][j]);
                }
            }
            repp(i,1,row) ve[i].clear();
            repp(i,1,row/2){
                ve[i]=tmp[i];
                tmp[i].clear();
            }
            row/=2; col*=2;
        }
        repp(i,1,row){
            repp(j,0,col-1){
                printf("%d ",ve[i][j]);
            }
        }
        printf("\n");
    }
    return QAQ;
}