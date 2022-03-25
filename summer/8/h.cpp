#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
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
const int maxn = 200 + 5;

namespace ACAM {
    static const int maxp = 100000 + 5;
    int sz, ch[maxp][6], fail[maxp];
    int match[maxp], val[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0; val[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 6; i++) ch[0][i] = 1;
    }
    void insert(int* s, int n, int i) {
        int u = 1;
        for (int i = 1; i <= n; i++) {
            int v = s[i];
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        val[u] = 1; match[i] = u;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 6; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
    }
}
using namespace ACAM;

namespace Gauss {
    static const double eps = 1e-7;
    double a[maxn][maxn], ans[maxn];
    void init(int n) {
        for (int i = 0; i <= n + 1; i++) {
            ans[i] = 0;
            for (int j = 0; j <= n + 1; j++)
                a[i][j] = 0.0;
        }
    }
    bool get(int n) {
        for (int i = 1; i <= n; i++) {
            int r = i;
            for (int j = i + 1; j <= n; j++)
                if(abs(a[j][i]) > abs(a[r][i])) r = j;
            if (abs(a[r][i]) < eps) return false;
            swap(a[r], a[i]);
            double inv = a[i][i];
            for (int j = i; j <= n + 1; j++) a[i][j] /= inv;
            for (int j = i + 1; j <= n; j++) {
                double inv = a[j][i];
                for(int k = i; k <= n + 1; k++)
                    a[j][k] -= inv * a[i][k];
            }
        }
        for(int i = n; i >= 1; i--) {
            ans[i] = a[i][n + 1];
            for(int j = i + 1; j <= n; j++)
                ans[i] -= a[i][j] * ans[j];
        }
        return true;
    }
    void print(int n) {
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= n + 1; j++)
                printf("%lf ", a[i][j]);
    }
};

int n, l, a[maxn][maxn];
double dp[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        clear();
        scanf("%d%d", &n, &l);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= l; j++) {
                scanf("%d", &a[i][j]); a[i][j]--;
            }
            insert(a[i], l, i);
        }
        build();
        Gauss::init(sz);
        Gauss::a[1][sz + 1] = -1.0;
        for (int i = 1; i <= sz; i++) {
            Gauss::a[i][i] = -1.0;
            if (val[i]) continue;
            for (int j = 0; j < 6; j++) {
                Gauss::a[ch[i][j]][i] += 1.0 / 6.0;
            }
        }
        Gauss::get(sz);
        for (int i = 1; i <= n; i++) {
            printf("%.6lf%c", Gauss::ans[match[i]], " \n"[i == n]);
        }
    }
    return 0;
}