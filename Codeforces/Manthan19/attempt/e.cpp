#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <functional>
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
const int maxn = 1000000 + 5;

int n, w;
ll ans[maxn];
vector<int> line[maxn];

int dp[21][maxn];
void build(const vector<int>& a) {
    int n = (int)a.size();
    if (n == w) {
        for (int i = 1; i <= w; i++) {
            ans[i] += a[i - 1];
            ans[i + 1] -= a[i - 1];
        }
        return ;
    }
    for (int i = 0; i < n; i++) dp[0][i] = i;
    for (int j = 1; j <= 20; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            int l = dp[j - 1][i];
            int r = dp[j - 1][i + (1 << (j - 1))];
            if (a[l] > a[r]) dp[j][i] = l;
            else dp[j][i] = r;
        }
    }
    auto qmax = [&](int l, int r) -> int {
        int k = __lg(r - l + 1);
        int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
        if (a[x] > a[y]) return x;
        else return y;
    };
    set<PII> seg;
    function<void(int,int)> solve = [&](int l, int r) {
        if (l > r) return ;
        int pos = qmax(l, r);
        if (a[pos] < 0) return ;
        int tl = pos + 1;
        int tr = w - n + pos + 1;
        int tl2 = tl, tr2 = tr;
        auto it = seg.upper_bound({tl, tr});
        if (it != seg.end()) {
            int ml = it->first, mr = it->second;
            if (ml <= tr) {
                tr = ml - 1;
            }
        }
        if (it != seg.begin()) {
            it--;
            int ml = it->first, mr = it->second;
            if (mr >= tl) {
                tl = mr + 1;
            }
        }
        if (tl <= tr) {
            ans[tl] += a[pos];
            ans[tr + 1] -= a[pos];
        }
        seg.insert({tl2, tr2});
        // dbg(l, r, pos, tl, tr);
        solve(l, pos - 1); solve(pos + 1, r);
    };
    solve(0, n - 1);
}

int main() {
    scanf("%d%d", &n, &w);
    for (int i = 1, x, m; i <= n; i++) {
        scanf("%d", &m);
        vector<int> line;
        for (int j = 1; j <= m; j++) {
            scanf("%d", &x);
            line.push_back(x);
        }
        build(line);
    }
    for (int i = 1; i <= w; i++) ans[i] += ans[i - 1];
    for (int i = 1; i <= w; i++) printf("%I64d ", ans[i]);
    return 0;
}