#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, m, h, q;

void gmax(int& a, int b) {
    if (a < b) a = b;
}
void gmin(int& a, int b) {
    if (a > b) a = b;
}

struct BIT {
    int a[maxn];
    inline int lowbit(int x) { return x & -x; }
    inline int gid(int x, int y, int z) {
        return x * m * h + y * h + z;
    }
    void clear() {
        for (int i = 0; i < maxn; i++) a[i] = -inf;
    }
    void update(int x, int y, int z, int val) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                for (int k = z; k <= h; k += lowbit(k)) {
                    gmax(a[gid(i, j, k)], val);
                }
            }
        }
    }
    int query(int x, int y, int z) {
        int r = -inf;
        for (int i = x; i; i -= lowbit(i)) {
            for (int j = y; j; j -= lowbit(j)) {
                for (int k = z; k; k -= lowbit(k)) {
                    r = max(r, a[gid(i, j, k)]);
                }
            }
        }
        return r;
    }
} f[8];

int main() {
    for (int i = 0; i < 8; i++) f[i].clear();
    scanf("%d%d%d%d", &n, &m, &h, &q);
    int op, x, y, z, cnt = 0;
    while (q--) {
        scanf("%d%d%d%d", &op, &x, &y, &z);
        if (op == 1) {
            f[0].update(x, y, z, x + y + z);
            f[1].update(x, y, h - z + 1, x + y - z);
            f[2].update(x, m - y + 1, z, x - y + z);
            f[3].update(x, m - y + 1, h - z + 1, x - y - z);
            f[4].update(n - x + 1, y, z, -x + y + z);
            f[5].update(n - x + 1, y, h - z + 1, -x + y - z);
            f[6].update(n - x + 1, m - y + 1, z, -x - y + z);
            f[7].update(n - x + 1, m - y + 1, h - z + 1, -x - y - z);
        } else if (op == 2) {
            int ans = inf;
            gmin(ans, x + y + z - f[0].query(x, y, z));
            gmin(ans, x + y - z - f[1].query(x, y, h - z + 1));
            gmin(ans, x - y + z - f[2].query(x, m - y + 1, z));
            gmin(ans, x - y - z - f[3].query(x, m - y + 1, h - z + 1));
            gmin(ans, -x + y + z - f[4].query(n - x + 1, y, z));
            gmin(ans, -x + y - z - f[5].query(n - x + 1, y, h - z + 1));
            gmin(ans, -x - y + z - f[6].query(n - x + 1, m - y + 1, z));
            gmin(ans, -x - y - z - f[7].query(n - x + 1, m - y + 1, h - z + 1));
            printf("%d\n", ans);
        }
    }
    return 0;
}