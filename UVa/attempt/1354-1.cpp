#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 12;
int n, idx, f[MAXN], w[MAXN];
double r, ans, rw[MAXN], lw[MAXN];

void build_binary_tree(int dep) {
    if (dep == n) return;
    for (int i = 0; i < MAXN; i++) if (f[i])
        for (int j = 0; j < MAXN; j++) if (i != j && f[j]) {
                double L = max(lw[i], lw[j] - 1), R = max(rw[i] - 1, rw[j]);
                if (1 + L + R < r) {
                    if (dep == n - 1) ans = max(1 + L + R, ans);        
                    f[i] = f[j] = 0;                                    
                    int id = idx++;
                    f[id] = 1;
                    w[id] = w[i] + w[j];
                    lw[id] = w[j] * 1.0 / w[id] + L;
                    rw[id] = w[i] * 1.0 / w[id] + R;
                    build_binary_tree(dep + 1);
                    f[--idx] = 0;
                    f[i] = f[j] = 1;
                }
            }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lf%d", &r, &n);
        ans = -1; idx = 0;
        memset(f, 0, sizeof(f));
        memset(rw, 0.0, sizeof(rw));
        memset(lw, 0.0, sizeof(lw));
        for (int i = 0; i < n; i++) {
            scanf("%d", &w[i]);
            f[idx++] = 1;
        }
        if (n == 1) {printf("0.0000000000\n"); continue;}
        build_binary_tree(1);
        printf("%.10lf\n", ans);
    }
    return 0;
}