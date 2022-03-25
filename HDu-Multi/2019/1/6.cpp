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
const int maxn = 200000 + 5;

namespace SA {
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
    int qmax(int l, int r) {
        int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
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

int dp[maxn][20];
void init(int n){
    for (int i = 1; i <= n; i++) dp[i][0] = SA::sa[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int l, int r){
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int query1(int l, int r, int id) {
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (rmq(m, r) <= id) ans = m, l = m + 1;
        else r = m - 1;
    }
    if (ans == -1) return -1;
    int hh = SA::qlcp(SA::sa[ans], id), mn = SA::sa[ans];
    while (ans >= 1 && SA::qlcp(SA::sa[ans], id) == hh) {
        mn = min(mn, SA::sa[ans]); ans--;
    }
    return SA::x[mn];
}
int query2(int l, int r, int id) {
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (rmq(l, m) <= id) ans = m, r = m - 1;
        else l = m + 1;
    }
    if (ans == -1) return -1;
    int hh = SA::qlcp(SA::sa[ans], id), mn = SA::sa[ans];
    while (ans <= SA::n && SA::qlcp(SA::sa[ans], id) == hh) {
        mn = min(mn, SA::sa[ans]); ans++;
    }
    return SA::x[mn];
}

int n, pp, q;
char s[maxn];

int main() {
    while (scanf("%s%d%d", s + 1, &pp, &q) == 3) {
        SA::build(n = strlen(s + 1), s);
        init(n);
        ll ans = pp;
        for (int i = 2; i <= n; ) {
            int a = query1(1, SA::x[i] - 1, i);
            int b = query2(SA::x[i] + 1, n, i);
            int mx = -1, p = -1;
            if (a != -1) {
                a = SA::sa[a];
                int tot = SA::qlcp(a, i);
                if (tot > mx) {
                    mx = tot; p = a;
                }
            }
            if (b != -1) {
                b = SA::sa[b];
                int tot = SA::qlcp(b, i);
                if (tot > mx) {
                    mx = tot; p = b;
                } else if (tot == mx) {
                    p = min(p, b);
                }
            }
            if (mx <= 0) {
                // printf("-1 %d\n", (int)s[i]);
                ans += pp; i++;
            } else {
                // printf("%d %d\n", mx, p - 1);
				mx = min(mx, i - p);
                ans += min(1ll * q, 1ll * mx * pp);
                i += mx;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}