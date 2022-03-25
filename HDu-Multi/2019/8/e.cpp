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
const int maxn = 500000 + 5;

int n, k;
char s[maxn];

namespace Power {
    struct SA {
        int n, m, sa[maxn], h[maxn], c[maxn], x[maxn], y[maxn];
        void rsort() {
            for (int i = 1; i <= m; i++) c[i] = 0;
            for (int i = 1; i <= n; i++) c[x[i]]++;
            for (int i = 1; i <= m; i++) c[i] += c[i - 1];
            for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
        }
        int cmp(int i, int j, int k) {
            int a = i + k > n ? -1 : y[i + k];
            int b = j + k > n ? -1 : y[j + k];
            return y[i] == y[j] && a == b;
        }
        int dp[maxn][21];
        void build(int nn, char* s) {
            n = nn; m = 255;
            for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
            rsort();
            for (int k = 1, p; k <= n; k += k, m = p) {
                p = 0;
                for (int i = n; i > n - k; i--) y[++p] = i;
                for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
                rsort(); 
                for (int i = 1; i <= n; i++) swap(x[i], y[i]);
                x[sa[1]] = p = 1;
                for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
            }
            for (int i = 1; i <= n; i++) x[sa[i]] = i;
            for (int i = 1, k = 0; i <= n; i++) {
                if (k) k--;
                int j = sa[x[i] - 1];
                while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
                h[x[i]] = k;
            }
            for (int i = 1; i <= n; i++) dp[i][0] = h[i];
            for (int j = 1; j < 21; j++) {
                for (int i = 1; i + (1 << j) <= n + 1; i++) {
                    dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
        int qlcp(int l, int r) {
            if (l == r) return n - l + 1;
            l = x[l]; r = x[r];
            if (l > r) swap(l, r);
            l++; int k = __lg(r - l + 1);
            return min(dp[l][k], dp[r - (1 << k) + 1][k]);
        }
    } ori, rev;

    const int maxr = 2e7 + 5;
    int tot, cov[maxr], si[maxn];
    ll get(int kk) {
        ll ans = 0;
        ms(cov, 0); ms(si, 0);

        ori.build(n, s);
        reverse(s + 1, s + n + 1);
        rev.build(n, s);
        
        for (int i = 1; i <= n; i++) si[i] = si[i - 1] + n / i;
        for (int len = 1; len + len <= n; len++) {
            int l = 0, r = 0;
            for (int i = len; i + len <= n; i += len) {
                if(i <= r) continue;
                int lcp = ori.qlcp(i, i + len);
                int lcs = rev.qlcp(n - i + 1, n - (i + len) + 1);
                if (lcp + lcs < len + 1) continue;
                l = i - lcs + 1; r = i + lcp - 1;
                if (cov[si[len - 1] + i / len]) continue;
                for (int x = len + len; l + x + x - 1 <= r + len; x += len)
                    cov[si[x - 1] + (l + x - 1) / x] = 1;
                for (int k = l; k <= r - len + 1 && k < l + len; k++) {
                    int n = (r - k + 1) / len + 1;
                    dbg(k, r + len, n);
                    int t = n / kk;
                    ans += 1ll * t * (n + 1) - 1ll * kk * (t * (t + 1) / 2);
                }
            }
        }
        return ans;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &k, s + 1);
        n = strlen(s + 1);
        if (k == 1) {
            printf("%lld\n", 1ll * n * (n + 1) / 2);
            continue;
        }
        printf("%lld\n", Power::get(k));
    }
    return 0;
}