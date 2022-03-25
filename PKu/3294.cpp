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
const int maxn = 200000 + 5;

char tmp[maxn];
int n, m, s[maxn], bel[maxn];
vector<int> res;

namespace SA {
    int n, m, sa[maxn], x[maxn], y[maxn], c[maxn], h[maxn];
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
        n = nn; m = 255; // important
        for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
        rsort();
        for (int k = 1, p; k <= n; k += k, m = p) {
            p = 0;
            for (int i = n; i > n - k; i--) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            rsort();
            // swap(x, y); 
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
    int vis[105];
    int check(int k, int mn) {
        // dbg(k, mn);
        int cnt = 0; ms(vis, 0);
        vector<int> tot;
        for (int i = 1; i <= n; i++) {
            if (h[i] >= k) {
                if (!vis[bel[sa[i]]]) cnt++, vis[bel[sa[i]]] = 1;
                if (!vis[bel[sa[i - 1]]]) cnt++, vis[bel[sa[i - 1]]] = 1;
            } else {
                if (cnt > mn) tot.push_back(sa[i - 1]);
                cnt = 0; ms(vis, 0);
            }
        }
        if (cnt > mn) tot.push_back(sa[n]);
        if (tot.empty()) return 0;
        res = tot;
        return 1;
    }
}

int main() {
    int kase = 0;
    while (scanf("%d", &n) && n) {
        m = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%s", tmp);
            for (int j = 0; tmp[j]; j++) s[++m] = (int)tmp[j], bel[m] = i;
            s[++m] = (int)'z' + i + 1; bel[m] = i;
        }
        if (n == 1) {
            puts(tmp); continue;
        }
        SA::build(--m, s);
        int l = 1, r = m, len = -1;
        vector<int> ans;
        while (l <= r) {
            int m = (l + r) / 2;
            if (SA::check(m, n / 2)) len = m, ans = res, l = m + 1;
            else r = m - 1;
        }
        if (kase++) puts("");
        if (len == -1) puts("?");
        else {
            for (int i = 0; i < (int)ans.size(); i++) {
                for (int j = ans[i]; j < ans[i] + len; j++) putchar(s[j]);
                puts("");
            }
        }
    }
    return 0;
}