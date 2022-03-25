#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 1000000 + 5;
const int maxs = (1 << 20) + 5;

char s[maxn];
int n, dp[maxs][21];
vector<PII> st[maxn], ed[maxn];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        int mask = 0;
        for (int j = i; j <= n; j++) {
            if (mask & (1 << (s[j] - 'a'))) break;
            else {
                mask |= 1 << (s[j] - 'a');
                st[i].push_back({j, mask});
                ed[j].push_back({i, mask});
                // dbg(i, j);
                // dp[mask] = i;
                dp[mask][j - i] = i;
            }
        }
    }
    int ss = (1 << 20) - 1;
    auto join = [&](int* s1, int* s2) {
        for (int i = 0; i < 20; i++) s1[i] = max(s1[i], s2[i]);
    };
    for (int i = 0; i < 20; i++) {
        for (int mask = 0; mask < (1 << 20); mask++) {
            if (mask & (1 << i)) {
                join(dp[mask], dp[mask ^ (1 << i)]);
            }
        }
    }
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        for (auto& p: ed[i]) {
            int len = 0, mask = ss ^ p.second;
            for (int i = 0; i < 20; i++) {
                if (dp[mask][i] > p.first) len = i + 1;
            }
            ans = max(ans, i - p.first + 1 + len);
        }
    }
    cout << ans;
    return 0;
}