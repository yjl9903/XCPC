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
const int maxn = 100 + 5;

namespace Gauss {
    static const double eps = 1e-7;
    double a[maxn][maxn], ans[maxn];
    void init(int n) {
        for (int i = 0; i <= n + 1; i++) {
            ans[i] = 0;
            for (int j = 0; j <= n + 1; j++)
                a[i][j] = 0;
        }
    }
    bool get(int n) {
        for (int i = 1; i <= n; i++) {
            int r = i;
            for (int j = i + 1; j <= n; j++)
                if(abs(a[j][i]) > abs(a[r][i])) r = j;
            if (abs(a[r][i]) < eps) return false;
            swap(a[r], a[i]);
            double inv = a[i][i];
            for (int j = i; j <= n + 1; j++) a[i][j] /= inv;
            for (int j = i + 1; j <= n; j++) {
                double inv = a[j][i];
                for(int k = i; k <= n + 1; k++)
                    a[j][k] -= inv * a[i][k];
            }
        }
        for(int i = n; i >= 1; i--) {
            ans[i] = a[i][n + 1];
            for(int j = i + 1; j <= n; j++)
                ans[i] -= a[i][j] * ans[j];
        }
        return true;
    }
    void print(int n) {
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= n + 1; j++)
                printf("%lf ", a[i][j]);
    }
}
using namespace Gauss;

int n, b[maxn][maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            scanf("%d", &b[i][j]);
            a[i][j] = 1.0 * b[i][j];
        }
    }
    if (!get(n)) return puts("No Solution"), 0;
    for (int i = 1; i <= n; i++) printf("%.2lf\n", ans[i]);
    return 0;
}