#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;
const int sz = 1500;

struct Que {
    int l, r, c, id, t;
    bool operator<(const Que& b) const {
        if (l / sz == b.l / sz) {
            if (r / sz == b.r / sz) {
                return id < b.id;
            }
            return r / sz < b.r / sz;
        }
        return l / sz < b.l / sz;
    }
} q[maxn];

int n, m, m1, m2, a[maxn], b[maxn], ans[maxn];

int p[maxn], c[maxn], pre[maxn];
int res = 0, bag[maxn];
void add(int x) {
    bag[x]++;
    if (bag[x] == 1) res++;
}
void del(int x) {
    bag[x]--;
    if (bag[x] == 0) res--;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
    for (int i = 1; i <= m; i++) {
        char op[3];
        scanf("%s", op);
        if (op[0] == 'Q') {
            m1++;
            q[m1].id = m1; q[m1].t = m2;
            scanf("%d%d", &q[m1].l, &q[m1].r);
        } else {
            m2++;
            scanf("%d%d", p + m2, c + m2);
            pre[m2] = b[p[m2]]; b[p[m2]] = c[m2];
        }
    }
    sort(q + 1, q + 1 + m1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= m1; i++) {
        while (r < q[i].r) add(a[++r]);
        while (r > q[i].r) del(a[r--]);
        while (l > q[i].l) add(a[--l]);
        while (l < q[i].l) del(a[l++]);
        while (t < q[i].t) {
            t++;
            if (l <= p[t] && p[t] <= r) {
                del(a[p[t]]); add(c[t]);
            }
            swap(c[t], a[p[t]]);
        }
        while (t > q[i].t) {
            if (l <= p[t] && p[t] <= r) {
                del(a[p[t]]); add(c[t]);
            }
            swap(c[t], a[p[t]]);
            t--;
        }
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= m1; i++) {
        // dbg(q[i].t);
        printf("%d\n", ans[i]);
    }
    return 0;
}