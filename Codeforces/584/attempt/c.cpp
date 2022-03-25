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
const int maxn = 200000 + 5;

int n, ans[maxn], pos[maxn];
char d[maxn], dp[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, d + 1);
        for (int i = 1; i <= n; i++) ans[i] = 2;
        int len = 1;
        dp[1] = d[1]; pos[1] = 1;
        for (int i = 2; i <= n; i++){
            if (d[i] >= dp[len]) dp[++len] = d[i], pos[i] = len;
            else {
                int k = upper_bound(dp + 1, dp + 1 + len, d[i]) - dp;
                dp[k] = d[i]; pos[i] = k;
            }
        }
        // for (int i = 1; i <= len; i++) cout << dp[i] << endl;
        // dbg(len);
        int p = len;
        for (int i = n; i >= 1 && p; i--) {
            if (pos[i] == p) {
                ans[i] = 1; p--;
            }
        }
        vector<int> v;
        for (int i = 1; i <= n; i++) if (ans[i] == 1) v.push_back(d[i] - '0');
        for (int i = 1; i <= n; i++) if (ans[i] == 2) v.push_back(d[i] - '0');
        int flag = 1;
        for (int i = 1; i < n; i++) if (v[i] < v[i - 1]) {
            flag = 0; break;
        }
        if (flag) {
            for (int i = 1; i <= n; i++) putchar(ans[i] + '0');
            puts("");
        } else {
            puts("-");
        }
    }
    return 0;
}