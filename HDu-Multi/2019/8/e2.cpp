#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
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

ll ans;
int n, k;
char s[maxn];

namespace Runs {
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
        void build(int nn, const char* s) {
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
            if (l < 1 || l > n) return 0;
            if (r < 1 || r > n) return 0;
            if (l == r) return n - l + 1;
            l = x[l]; r = x[r];
            if (l > r) swap(l, r);
            l++; int k = __lg(r - l + 1);
            return min(dp[l][k], dp[r - (1 << k) + 1][k]);
        }
    } ori, rev;
    
    int n; char s[maxn];
    
    bool cmp(int x, int y) {
        int len = ori.qlcp(x, y);
        if (x + len > n) return false;
        if (y + len > n) return true;
        return s[x + len] < s[y + len];
    }

    map<PII,int> mp;
    void add(int l, int r, int p) {
        if (mp.count({l, r})) return ;
        // Run => (l, r, p)
        mp[{l, r}] = 1;
        for (int i = 0; i < p * 2 && l + 2 * p - 1 + i <= r; i++) {
            for (int j = l + 2 * p - 1 + i; j <= r; j += 2 * p) {
                // Primitive Square: [j-2p+1,j]
            }
        }
        for (int i = l; i < l + p; i++) {
            // primitive x power string [i,i+px-1]
            int x = (r - i + 1) / p;
            dbg(i, i + p * x - 1, x);
            int t = x / k;
            ans += 1ll * t * (x + 1) - 1ll * k * (t * (t + 1) / 2);
        }
    }
    void check(int l, int r) {
        int len = r - l;
        int lcp = ori.qlcp(l, r);
        int lcs = rev.qlcp(n - l + 2, n - r + 2);
        if (lcp + lcs >= len) {
            add(l - lcs, r + lcp - 1, len);
        }
    }
    void find(int type) {
        static int st[maxn], stn;
        stn = 0; st[stn++] = n + 1;
        for (int i = n; i >= 1; i--) {
            while (stn > 1 && cmp(i, st[stn - 1]) == type) stn--;
            check(i, st[stn - 1]);
            st[stn++] = i;
        }
    }
    void build(int nn, char* ss) {
        n = nn;
        for (int i = 1; i <= n; i++) s[i] = ss[i];
        s[n + 1] = 0;
        ori.build(n, ss);
        reverse(ss + 1, ss + n + 1);
        rev.build(n, ss);

        mp.clear();
        find(0); find(1);
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
        ans = 0;
        Runs::build(n, s);
        printf("%lld\n", ans);
    }
    return 0;
}