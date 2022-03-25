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
const int maxn = 50 + 5;

int n, m, a[maxn][maxn], b[maxn][maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] > b[i][j]) swap(a[i][j], b[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (a[i][j] <= a[i - 1][j] || a[i][j] <= a[i][j - 1]) return puts("Impossible");
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (b[i][j] <= b[i - 1][j] || b[i][j] <= b[i][j - 1]) return puts("Impossible");
    }
    puts("Possible");
    return 0;
}