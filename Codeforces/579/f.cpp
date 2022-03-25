#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 300000 + 5;

int n, r;
set<int> dp[maxn];
PII a[500];

int main() {
    scanf("%d%d", &n, &r);
    multiset<PII> add;
    vector<int> sub;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        if (a[i].second >= 0) add.insert(a[i]);
        else sub.push_back(i);
    }
    int ans = 0, res = 0;
    while (!add.empty() && r >= add.begin()->first) {
        r += add.begin()->second;
        add.erase(add.begin());
        ans++;
    }
    for (int i = r; i >= 1; i--) {
        if ((int)dp[i].size() < (int)dp[i + 1].size()) dp[i] = dp[i + 1];
        res = max(res, (int)dp[i].size());
        for (int id: sub) {
            if (a[id].first > i) continue;
            if (i + a[id].second < 0) continue;
            if (dp[i].count(id)) continue;
            int tg = i + a[id].second;
            if ((int)dp[tg].size() < (int)dp[i].size() + 1) {
                dp[tg] = dp[i]; dp[tg].insert(id);
            }
        }
    }
    // dbg(res);
    if (ans + res == n) puts("YES");
    else puts("NO");
    // printf("%d\n", ans + res);
    return 0;
}