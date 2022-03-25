#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,ll> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

vector<PII> edge[maxn];
int n, m;
ll a[maxn], ww[maxn];
ll ans[maxn], dp[maxn];

bool vis[maxn]; ll dis[maxn];
struct node{
    int to; ll d;
    bool operator< (const node& b)const{
        return d > b.d;
    }
};

void dijkstra(){
    ms(vis, 0); dis[0] = 0;
    for (int i = 1; i <= n; i++) 
    	dis[i] = 1ll << 60;
    priority_queue<node> q;
    q.push({0, 0}); 
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (vis[t.to]) continue;
        vis[t.to] = 1;
        for (auto& x: edge[t.to]) {
            int v = x.first;
            if (vis[v]) continue;
            if (dis[v] > dis[t.to] + x.second){
                dis[v] = dis[t.to] + x.second;
                q.push({v, dis[v]});
            }
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        ll w; scanf("%d%d%I64d", &u, &v, &w);
        edge[u].push_back({v, w * 2});
        edge[v].push_back({u, w * 2});
    }
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", a + i);
        edge[0].push_back({i, a[i]});
    }
    dijkstra();
    for (int i = 1; i <= n; i++) {
        printf("%lld ", dis[i]);
    }
    return 0;
}