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
const int maxn = 1000 + 5;

int n, m, a[maxn][maxn], q1[maxn], q2[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int ans = 1;
        for (int up = 1; up <= n; up++) {
            vector<int> mx(n + 1, -1), mn(n + 1, inf);
            for (int dw = up; dw <= n; dw++) {
                int l1 = 1, r1 = 0, l2 = 1, r2 = 0, le = 1;
                for (int i = 1; i <= n; i++) {
                    mx[i] = max(mx[i], a[dw][i]);
                    mn[i] = min(mn[i], a[dw][i]);
                    while (l1 <= r1 && mx[q1[r1]] <= mx[i]) r1--;
                    q1[++r1] = i;
                    while (l2 <= r2 && mn[q2[r2]] >= mn[i]) r2--;
                    q2[++r2] = i;
                    while (le <= i && mx[q1[l1]] - mn[q2[l2]] > m) {
                        le++;
                        while (l1 <= r1 && q1[l1] < le) l1++;
                        while (l2 <= r2 && q2[l2] < le) l2++;
                    }
                    if (i >= le) ans = max(ans, (dw - up + 1) * (i - le + 1));
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}