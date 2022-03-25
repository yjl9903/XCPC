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

char s[maxn], suf[maxn];
int n, k, nxt[maxn][26];

namespace sa {
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
        l++;
        int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &k, s + 1);
        n = strlen(s + 1);
        for (int j = 0; j < 26; j++) nxt[n][j] = nxt[n + 1][j] = n + 1;
        suf[n] = s[n];
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = max(suf[i + 1], s[i]);
            for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
            nxt[i][s[i + 1] - 'a'] = i + 1;
        }
        string ans; int pos = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i] == suf[i]) {
                ans += s[i]; pos = i;
            } else {
                break;
            }
        }
        for (int t = 1; t < k; t++) {
            if (pos > n) break;
            for (int j = 25; j >= 0; j--) {
                if (nxt[pos][j] > n) continue;
                int nx = nxt[pos][j];
                // ans += s[nx];
                pos = nx;
                // dbg(t, pos, nx);
                for (; pos <= n && s[pos] == suf[pos]; pos++) {
                    ans += s[pos];
                }
                pos--;
                break;
            }
        }
        // dbg(pos);
        sa::build(n, s);
        int mxsuf = 0, mxp = -1;
        for (int i = pos + 1; i <= n; i++) {
            if (sa::x[i] > mxsuf) {
                mxsuf = sa::x[i];
                mxp = i;
            }
        }
        if (mxp > -1) {
            for (int i = mxp; i <= n; i++) ans += s[i];
        }
        printf("%s\n", ans.c_str());
    }
    return 0;
}