#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 200000 + 5;

int n, b[maxn];
PII a[maxn];

void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}

ll dp[maxn];
int q[maxn];

int main() {
    scanf("%d", &n);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        lsh.push_back(a[i].second);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    sort(a + 1, a + 1 + n);
    vector<PII> key;
    for (int i = n; i >= 1; i--) {
        int pos = lower_bound(lsh.begin(), lsh.end(), a[i].second) - lsh.begin() + 1;
        int cnt = query(pos);
        if (cnt == n - i) key.push_back(a[i]);
        update(pos, 1);
    }
    reverse(key.begin(), key.end());
    for (auto x: key) dbg(x.first, x.second);
    dp[0] = 0; 
    dp[1] = 1ll * key[0].first * key[0].second;
    int l = 1, r = 1; q[1] = 1;
    auto gu = [&](int i, int j) -> ll {
        return dp[i] - dp[j];
    };
    auto gd = [&](int i, int j) -> ll {
        return key[i].second - key[j].second;
    };
    for (int i = 1; i < (int)key.size(); i++) {
        while (l < r && gu(q[l + 1], q[l]) + key[i].first * gd(q[l + 1], q[l]) < 0) l++;
        if (l <= r) {
            int j = q[l];
            dp[i + 1] = dp[j] + 1ll * key[i].first * key[j].second;
        }
        while (l < r && gu(q[r], q[r - 1]) * gd(i, q[r]) <= gu(i, q[r]) * gd(q[r], q[r - 1])) r--;
        q[++r] = i + 1;
    }
    cout << dp[(int)key.size()];
    return 0;
}