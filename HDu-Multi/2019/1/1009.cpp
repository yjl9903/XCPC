#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
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
const int maxn = 100000 + 5;

char s[maxn];
int n, k, l[30], r[30], nxt[maxn][26], cnt[maxn][26];

int main() {
    while (scanf("%s%d", s + 1, &k) == 2) {
        n = strlen(s + 1);
        for (int i = 0; i < 26; i++) scanf("%d%d", l + i, r + i);
        for (int j = 0; j < 26; j++) nxt[n + 1][j] = nxt[n][j] = cnt[n + 1][j] = 0;
        for (int i = n; i >= 0; i--) {
            for (int j = 0; j < 26; j++) cnt[i][j] = cnt[i + 1][j], nxt[i][j] = nxt[i + 1][j];
            if (i > 0) cnt[i][s[i] - 'a']++;
            if (i < n) nxt[i][s[i + 1] - 'a'] = i + 1;
        }
        int u = 0, no = 0; string ans; vector<int> use(26, 0);
        for (int t = 0; t < k; t++) {
            int vis = 0;
            for (int j = 0; j < 26; j++) {
                if (nxt[u][j] == 0) continue;
                dbg(u, nxt[u][j]);
                if (use[j] == r[j]) continue;
                int flag = 0, nx = nxt[u][j];
                // k - t - 1
                int sum = 0, sum2 = 0;
                use[j]++;
                for (int k = 0; k < 26; k++) {
                    if (use[k] + cnt[nx + 1][k] < l[k]) flag = 1;
                    sum += max(0, l[k] - use[k]);
                    sum2 += min(r[k] - use[k], cnt[nx + 1][k]);
                }
                use[j]--;
                if (sum > k - t - 1) flag = 1;
                // if (sum2 < k - t - 1) flag = 1;
                dbg(sum, k - t - 1);
                if (flag) continue;
                use[j]++; ans += j + 'a'; u = nxt[u][j];
                vis = 1; break;
            }
            if (vis == 0) {
                no = 1; break;
            }
        }
        if (no) puts("-1");
        else printf("%s\n", ans.c_str());
    }
    return 0;
}