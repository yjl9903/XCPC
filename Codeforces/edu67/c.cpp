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
const int maxn = 2000 + 5;

int n, m, qt[maxn], ql[maxn], qr[maxn];
int c[maxn], ans[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", qt + i, ql + i, qr + i);
        if (qt[i] == 1) {
            for (int j = ql[i]; j < qr[i]; j++) {
                c[j] = 1;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (qt[i] == 1) continue;
        int f = 0;
        for (int j = ql[i]; j < qr[i]; j++) {
            if (c[j] == 0) {
                f = 1; break;
            }
        }
        if (!f) return puts("NO"), 0;
    }
    puts("YES");
    ans[1] = 100000;
    for (int i = 1; i < n; i++) {
        if (c[i]) ans[i + 1] = ans[i];
        else ans[i + 1] = ans[i] - 1;
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}