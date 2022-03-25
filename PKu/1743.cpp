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
const int maxn = 1000000 + 5;

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
    void build(int nn, int* s) {
        n = nn; m = 400;
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
    }
    int check(int len) {
        int mx = sa[1], mn = sa[1];
        for (int i = 2; i <= n; i++) {
            if (h[i] >= len) {
                mn = min(mn, sa[i]);
                mx = max(mx, sa[i]);
                if (mx - mn > len) return 1;
            } else mx = sa[i], mn = sa[i];
        }
        return 0;
    }
}

int n, a[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        if (n == 0) return 0;
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i < n; i++) a[i] = a[i + 1] - a[i] + 100;
        n--; 
        SA::build(n, a);
        int l = 4, r = n, ans = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (SA::check(m)) ans = m + 1, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}