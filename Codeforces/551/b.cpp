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

int n, m, h, a[maxn], b[maxn], c[maxn][maxn];

int main() {
    scanf("%d%d%d", &n, &m, &h);
    for (int i = 1; i <= m; i++) scanf("%d", b + i);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &c[i][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[i][j] == 0) {
                printf("0 "); continue;
            }
            if (a[i] == b[j]) printf("%d ", a[i]);
            else printf("%d ", min(a[i], b[j]));
        }
        puts("");
    }
    return 0;
}