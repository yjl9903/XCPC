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
const int maxn = 1000000 + 5;

struct LinearBase {
    static const int M = 30;
    int a[M + 1], pos[M + 1];
    void clear() {
        ms(a, 0); ms(pos, 0);
    }
    LinearBase() { 
        clear();
    }
    int insert(int x, int id = 0) {
        for (int i = M; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) {
                    if (id > pos[i]) swap(id, pos[i]), swap(x, a[i]);
                    x ^= a[i];
                } else {
                    a[i] = x; pos[i] = id;
                    return true;
                }
            }
        }
        return false;
    }
    int query(int x, int l) {
        int ans = x;
        for (int i = M; i >= 0; i--) {
            if (pos[i] < l) continue;
            if ((ans ^ a[i]) >= ans) ans ^= a[i];
        }
        return ans;
    }
} pre[maxn];

int n, m;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x);
            pre[i] = pre[i - 1]; pre[i].insert(x, i);
        }
        int op, l, r, x, last = 0;
        while (m--) {
            scanf("%d", &op);
            if (op == 0) {
                scanf("%d%d", &l, &r);
                int a = (l ^ last) % n + 1, b = (r ^ last) % n + 1;
                if (a > b) swap(a, b);
                printf("%d\n", last = pre[b].query(0, a));
            } else {
                scanf("%d", &x); n++;
                pre[n] = pre[n - 1];
                pre[n].insert(last ^ x, n);
            }
        }
    }
    return 0;
}