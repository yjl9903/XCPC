#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 300000 + 5;

int n, m, u[maxn], v[maxn], deg[maxn], vis[maxn], mp[maxn];
vector<PII> edge[maxn];

int main(){
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", u + i, v + i);
            deg[u[i]]++; deg[v[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            if (deg[u[i]] != deg[v[i]]) {
                if (deg[u[i]] < deg[v[i]]) swap(u[i], v[i]);
            } else {
                if (u[i] > v[i]) swap(u[i], v[i]);
            }
            edge[u[i]].emplace_back(v[i], i);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (auto& v: edge[i]) vis[v.first] = v.second;
            for (auto& v: edge[i]) {
                for (auto& u: edge[v.first]) if (vis[u.first]) {
                    mp[v.second]++; mp[u.second]++; mp[vis[u.first]]++;
                }
            }
            for (auto& v: edge[i]) vis[v.first] = 0;
        }
        for (int i = 1; i <= m; i++) {
            ans += 1ll * mp[i] * (mp[i] - 1) / 2;
            mp[i] = 0;
        }
        printf("%lld\n", ans);
        for (int i = 0; i <= n; i++) edge[i].clear(), vis[i] = deg[i] = 0;
    }
    return 0;
}