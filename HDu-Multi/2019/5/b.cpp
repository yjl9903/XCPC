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
const int maxn = 100000 + 5;
const int maxm = maxn * 31;

struct Trie {
    int tot, ch[maxm][2], val[maxm];
    void clear() {
        tot = 1; ch[1][0] = ch[1][1] = 0; val[1] = 0;
    }
    void insert(int x, int y = 1) {
        int u = 1; val[u] += y;
        for (int i = 30; i >= 0; i--) {
            int b = x >> i & 1;
            if (!ch[u][b]) {
                ch[u][b] = ++tot;
                ch[tot][0] = ch[tot][1] = 0;
                val[tot] = 0;
            }
            u = ch[u][b];
            val[u] += y;
        }
    }
} a, b;

int n, ans[maxn];
PII w[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        a.clear(); b.clear();
        scanf("%d", &n);
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x); a.insert(x);
            ans[i] = 0;
            w[i].first = w[i].second = 1;
        }
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x); b.insert(x);
        }
        for (int t = 0; t <= 30; t++) {
            for (int i = 1; i <= n; i++) {
                int a0 = a.ch[w[i].first][0];
                int a1 = a.ch[w[i].first][1];
                int b0 = b.ch[w[i].second][0];
                int b1 = b.ch[w[i].second][1];
                if (a0 && b0 && a.val[a0] && b.val[b0]) {
                    a.val[a0]--; b.val[b0]--;
                    ans[i] <<= 1;
                    w[i].first = a0;
                    w[i].second = b0;
                } else if (a1 && b1 && a.val[a1] && b.val[b1]) {
                    a.val[a1]--; b.val[b1]--;
                    ans[i] <<= 1;
                    w[i].first = a1;
                    w[i].second = b1;
                } else if (a0 && b1 && a.val[a0] && b.val[b1]) {
                    a.val[a0]--; b.val[b1]--;
                    ans[i] <<= 1; ans[i] |= 1;
                    w[i].first = a0;
                    w[i].second = b1;
                } else if (a1 && b0 && a.val[a1] && b.val[b0]) {
                    a.val[a1]--; b.val[b0]--;
                    ans[i] <<= 1; ans[i] |= 1;
                    w[i].first = a1;
                    w[i].second = b0;
                }
            }
        }
        sort(ans + 1, ans + 1 + n);
        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], " \n"[i == n]);
        }
    }
    return 0;
}