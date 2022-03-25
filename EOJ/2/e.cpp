#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

vector<int> edge[maxn];
int n, m, a[maxn], b[maxn];

int vis[maxn], f[maxn];
int dp(int u) {
    if (vis[u]) return f[u];
    vis[u] = 1;
    for (int& v: edge[u]) {
        f[u] = max(f[u], b[v] + dp(v));
    }
    // dbg(u, f[u]);
    return f[u];
}
int check(int x) {
    for (int i = 1; i <= n; i++) if (a[i] >= x) b[i] = 1; else b[i] = -1;
    for (int i = 1; i <= n; i++) f[i] = -inf, vis[i] = 0; f[n] = 0;
    return b[1] + dp(1) >= 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    while (m--) {
        int u, v; scanf("%d%d", &u, &v); edge[u].push_back(v);
    }
    int l = 0, r = 1e9, ans = -1;
    // check(4);
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m)) ans = m, l = m + 1;
        else r = m - 1;
    }
    cout << ans << endl;
    return 0;
}