#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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
const int maxn = 500 + 5;

char s[maxn];
int n, ok[maxn][maxn], dp[maxn];

bool check(string s) {
    int n = s.length(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int t = s[(i + k) % n] - s[(j + k) % n];
        if (!t) k++;
        else {
            if (t > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    string tot;
    for (int p = min(i, j); p < n; p++) tot += s[p];
    for (int p = 0; p < min(i, j); p++) tot += s[p];
    return tot == s;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; i++) {
            string tot;
            for (int j = i; j <= n; j++) {
                tot += s[j];
                ok[i][j] = check(tot);
                // dbg(i, j, ok[i][j]);
            }
        }
        for (int i = 0; i <= n; i++) dp[i] = inf;
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (!ok[j][i]) continue;
                dp[i] = min(dp[i], dp[j - 1] + 1);
                // dbg(i, dp[i]);
            }
        }
        vector<string> ans; 
        for (int i = n; i >= 1;) {
            for (int j = i - 1; j >= 0; j--) {
                if (dp[j] + 1 == dp[i] && ok[j + 1][i]) {
                    string tot;
                    for (int p = j + 1; p <= i; p++) tot += s[p];
                    ans.push_back(tot);
                    i = j;
                    break;
                }
            }
        }
        reverse(ans.begin(), ans.end());
        // assert((int)ans.size() == dp[n]);
        if ((int)ans.size() < dp[n]) {
            for(;;);
        }
        for (int i = 0; i < dp[n]; i++) printf("%s%c", ans[i].c_str(), " \n"[i == dp[n] - 1]);
    }
    return 0;
}