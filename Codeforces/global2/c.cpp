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
const int maxn = 500 + 5;

int n, m, a[maxn][maxn], b[maxn][maxn];
int cntr[maxn], cntc[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != b[i][j]) {
                cntr[i]++; cntc[j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) if (cntr[i] % 2) return puts("No");
    for (int i = 1; i <= m; i++) if (cntc[i] % 2) return puts("No");
    puts("Yes");
    return 0;
}