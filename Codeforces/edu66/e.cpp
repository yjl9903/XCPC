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
const int maxn = 200000 + 5;
const int maxl = 500000 + 5;

int n, q, l[maxn], r[maxn], nxt[maxl][20];
vector<int> seg[maxl];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", l + i, r + i);
        seg[l[i]].push_back(r[i]);
    }
    int mx = -1;
    for (int i = 0; i < maxl; i++) {
        for (int& x: seg[i]) mx = max(mx, x);
        if (mx >= i) nxt[i][0] = mx;
        else nxt[i][0] = i;
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < maxl; i++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int x, y; scanf("%d%d", &x, &y);
        int now = x, ans = 0;
        if (nxt[x][19] < y) {
            puts("-1"); continue;
        }
        for (int i = 19; i >= 0; i--) {
            if (nxt[now][i] < y) {
                ans += 1 << i;
                now = nxt[now][i];
            }
        }
        if (now < y) ans++;
        printf("%d\n", ans);
    }
    return 0;
}