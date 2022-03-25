#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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

int n;
char s[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        set<int> st;
        scanf("%s", s + 1);
        SA::build(n = strlen(s + 1), s);
        printf("Case #%d:\n", ++kase);
        printf("-1 %d\n", (int)s[1]);
        for (int i = 2; i <= n; ) {
            int mx = -1, p = -1;
            for (int j = 1; j < i; j++) {
                int tot = SA::qlcp(j, i);
                if (tot > mx) {
                    mx = tot; p = j;
                }
            }
            if (mx <= 0 || st.count(p)) printf("-1 %d\n", (int)s[i]), i++;
            else {
                printf("%d %d\n", mx, p - 1); st.insert(p);
                i += mx;
            }
        }
    }
    return 0;
}