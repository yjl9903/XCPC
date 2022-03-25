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
const int maxn = 2000 + 5;

int n, a[maxn], f[maxn][maxn];

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; i++) scanf("%d", a + i), a[n + i] = a[i];
        ms(f, 0); for (int i = 1; i <= 2 * n; i++) f[i][i] = 1;
        // for (int i = 1; i <= 2 * n; i++) cout << a[i] << ' '; cout << endl;
        for (int len = 2; len <= 2 * n; len++) {
            for (int l = 1; l + len - 1 <= 2 * n; l++) {
                int r = l + len - 1;
                f[l][r] = max(f[l + 1][r], f[l][r - 1]);
                if (a[l] == a[r]) f[l][r] = max(f[l][r], f[l + 1][r - 1] + 2);
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, f[i][i + n - 1]);
        for (int i = 2; i <= n; i++) ans = max(ans, f[i][i + n - 2] + 1);
        printf("%d\n", ans);
    }
    return 0;
}