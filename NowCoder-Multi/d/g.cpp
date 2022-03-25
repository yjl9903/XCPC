#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;
const int N = 2e5 + 5;

namespace sa {
    int n, sa[maxn], rk[maxn], h[maxn], s[maxn<<1], t[maxn<<1], p[maxn], cnt[maxn], cur[maxn];
    #define pushS(x) sa[cur[s[x]]--] = x
    #define pushL(x) sa[cur[s[x]]++] = x
    #define inducedSort(v) \
        fill_n(sa, n, -1); fill_n(cnt, m, 0);                                         \
        for (int i = 0; i < n; i++) cnt[s[i]]++;                                      \
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];                             \
        for (int i = 0; i < m; i++) cur[i] = cnt[i] - 1;                              \
        for (int i = n1 - 1; ~i; i--) pushS(v[i]);                                    \
        for (int i = 1; i < m; i++) cur[i] = cnt[i - 1];                              \
        for (int i = 0; i < n; i++) if (sa[i] > 0 &&  t[sa[i] - 1]) pushL(sa[i] - 1); \
        for (int i = 0; i < m; i++) cur[i] = cnt[i] - 1;                              \
        for (int i = n-1;  ~i; i--) if (sa[i] > 0 && !t[sa[i] - 1]) pushS(sa[i] - 1);
    void sais(int n, int m, int *s, int *t, int *p) {
        int n1 = t[n - 1] = 0, ch = rk[0] = -1, *s1 = s + n;
        for (int i = n - 2; ~i; i--) t[i] = s[i] == s[i + 1] ? t[i + 1] : s[i] > s[i + 1];
        for (int i = 1; i < n; i++) rk[i] = t[i - 1] && !t[i] ? (p[n1] = i, n1++) : -1;
        inducedSort(p);
        for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
            if (ch < 1 || p[x + 1] - p[x] != p[y + 1] - p[y]) ch++;
            else for (int j = p[x], k = p[y]; j <= p[x + 1]; j++, k++)
                if ((s[j] << 1 | t[j]) != (s[k] << 1 | t[k])) {ch++; break;}
            s1[y = x] = ch;
        }
        if (ch + 1 < n1) sais(n1, ch + 1, s1, t + n, p + n1);
        else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
        for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
        inducedSort(s1);
    }
    template<typename T>
    int mapCharToInt(int n, const T *str) {
        int m = *max_element(str, str + n);
        fill_n(rk, m + 1, 0);
        for (int i = 0; i < n; i++) rk[str[i]] = 1;
        for (int i = 0; i < m; i++) rk[i + 1] += rk[i];
        for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
        return rk[m];
    }
    int dp[maxn][21];
    template<typename T>
    void build(int nn, const T *str) {
        n = nn;
        int m = mapCharToInt(++n, str);
        sais(n, m, s, t, p);
        for (int i = 0; i < n; i++) rk[sa[i]] = i;
        for (int i = 0, k = 0; i < n; i++) {
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            h[rk[i]] = k;
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
        l = rk[l]; r = rk[r];
        if (l > r) swap(l, r);
        l++; int k = __lg(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
};


int n, q, match[N], lens[N];
char s[maxn], t[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int len = -1;
        for (int i = 1; i <= n; i++) {
            scanf("%s", t + 1);
            lens[i] = strlen(t + 1);
            match[i] = len + 1;
            for (int j = 1; j <= lens[i]; j++) s[++len] = t[j];
        }
        s[++len] = 'a' - 1;
        sa::build(len, s);
        printf("Case %d:\n", ++kase);
        int u, v;
        scanf("%d", &q);
        while (q--) {
            scanf("%d%d", &u, &v);
            printf("%d\n", min(min(lens[u], lens[v]), sa::qlcp(match[u], match[v])));
        }
    }
    return 0;
}