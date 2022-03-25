#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int b[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}

int n, vis[maxn];
PII a[maxn];
vector<int> ev[maxn];

int main() {
    vector<int> lsh;
    ll ans = 0; int mx = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        lsh.push_back(a[i].first);
    }
    sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) {
        a[i].first = lower_bound(lsh.begin(), lsh.end(), a[i].first) - lsh.begin() + 1;
    }
    lsh.clear();
    for (int i = 1; i <= n; i++) lsh.push_back(a[i].second);
    sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) {
        a[i].second = lower_bound(lsh.begin(), lsh.end(), a[i].second) - lsh.begin() + 1;
        ev[a[i].second].push_back(a[i].first);
        mx = max(mx, a[i].second);
    }
    auto f = [](int x) -> ll {
        return 1ll * x * (x + 1) / 2ll;
    };
    int sum = 0;
    for (int i = mx; i >= 1; i--) {
        sort(ev[i].begin(), ev[i].end());
        ll tot = f(query(ev[i].front() - 1)) + f(sum - query(ev[i].back()));
        for (int j = 1; j < (int)ev[i].size(); j++) {
            if (ev[i][j - 1] + 1 == ev[i][j]) continue;
            int l = query(ev[i][j - 1]), r = query(ev[i][j] - 1);
            tot += f(r - l);
            dbg(l, r);
        }
        for (int j = 0; j < (int)ev[i].size(); j++) {
            if (vis[ev[i][j]]) continue;
            update(ev[i][j], 1);
            vis[ev[i][j]] = 1;
            sum++;
        }
        ans += f(sum) - tot;
        dbg(ans, sum, tot);
    }
    cout << ans;
    return 0;
}