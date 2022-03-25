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
const int maxn = 100000 + 5;

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

char s[maxn];
int n;

int main() {
    int kase = 0;
    while (scanf("%s", s + 1) == 1) {
        if (s[1] == '#') return 0;
        SA::build(n = strlen(s + 1), s);
        // for (int i = 1; i <= n; i++) {
        //     for (int j = i; j <= n; j++) {
        //         dbg(i, j, SA::qlcp(i, j));
        //     }
        // }
        int mx = 0; vector<int> ans;
        for (int l = 1; l <= n; l++) {
            for (int i = 1; i + l <= n; i += l) {
                int k = SA::qlcp(i, i + l);
                int tot = k / l + 1;
                int st = i - (l - k % l);
                if (st >= 0 && SA::qlcp(st, st + l) >= l - k % l) tot++;
                if (tot > mx) {
                    mx = tot;
                    ans.clear(); ans.push_back(l);
                } else if (tot == mx) {
                    ans.push_back(l);
                }
            }
        }
        printf("Case %d: ", ++kase);
        for (int i = 1; i <= n; i++) {
            int st = SA::sa[i], flag = 0;
            for (int x: ans) {
                if (SA::qlcp(st, st + x) >= (mx - 1) * x) {
                    for (int j = st; j < st + mx * x; j++) putchar(s[j]);
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        puts("");
    }
    return 0;
}