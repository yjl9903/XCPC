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

struct LinearBase {
    static const int M = 21;
    int a[M + 5], pos[M + 5], sz;
    void clear() {
        ms(a, 0); ms(pos, 0); sz = 0;
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
                    a[i] = x; pos[i] = id; sz++;
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

int n, q;

int main() {
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
        pre[i] = pre[i - 1];
        scanf("%d", &x); pre[i].insert(x, i);
    }
    scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", pre[r].query(0, l));
    }
    return 0;
}