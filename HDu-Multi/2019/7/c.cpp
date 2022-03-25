#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, ans;
vector<int> edge[maxn];

ull ha[maxn];
map<ull,int> mp[maxn];
map<ull,int>::iterator it;
void dfs(int u, int f) {
    ha[u] = (ull)u;
    ans++;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        mp[u][ha[v]]++;
    }
    for (it = mp[u].begin(); it != mp[u].end(); it++) {
        ans += it->second;
    }
    // for (auto x: mp[u]) {
    //     ans += x.second;
    // }
}

int main() {
    // freopen("./input/text.txt", "r", stdin);
    int T; scanf("%d", &T);
    cout << T << endl;
    while (T--) {
        scanf("%d", &n);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}