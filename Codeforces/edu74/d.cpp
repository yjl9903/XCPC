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
const int maxn = 300000 + 5;

char s[maxn];
int n, nxt[maxn][2], len[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    ll ans = 1ll * (n + 1) * n / 2 - n;
    nxt[n][0] = nxt[n][1] = -1;
    len[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        nxt[i][0] = nxt[i + 1][0];
        nxt[i][1] = nxt[i + 1][1];
        if (s[i] == s[i + 1]) {
            len[i] = len[i + 1] + 1;
        } else {
            len[i] = 1;
        }
        nxt[i][s[i + 1] - 'A'] = i + 1;
    }
    for (int i = 1; i <= n; i++) {
        int ch = s[i] - 'A';
        if (nxt[i][ch ^ 1] != -1) {
            int u = nxt[i][ch ^ 1];
            ans--;
            if (u == i + 1) {
                ans -= len[u] - 1;
            }
        }
    }
    cout << ans;
    return 0;
}