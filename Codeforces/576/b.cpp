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
const int maxn = 500000 + 5;

int n, q, a[maxn], last[maxn];
int op[maxn], p[maxn], x[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", op + i);
        if (op[i] == 1) {
            scanf("%d%d", p + i, x + i);
            last[p[i]] = i;
        } else scanf("%d", x + i);
    }
    int suf = -1;
    for (int i = q; i >= 1; i--) {
        if (op[i] == 1) {
            if (i == last[p[i]]) {
                a[p[i]] = max(suf, x[i]);
            }
        } else if (op[i] == 2) {
            suf = max(suf, x[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (last[i]) printf("%d ", a[i]);
        else printf("%d ", max(suf, a[i]));
    }
    return 0;
}