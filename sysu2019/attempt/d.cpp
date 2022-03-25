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

struct Ope {
    int l, r, f, id; bool tp;
    bool operator<(const Ope& b) const {
        if (l == b.l) return r < b.r;
        return l < b.l;
    }
};
vector<Ope> v;

int n, m, p, q;

ll a[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    if (i == 0) return ;
    for (; i <= m + 1; i += lowbit(i)) a[i] += x;
}
inline ll query(int i) {
    ll ans = 0;
    for (; i; i -= lowbit(i)) ans += a[i];
    return ans;
}

ll ans[maxn];
// int x1[2][maxn], y1[2][maxn], x2[2][maxn], y2[2][maxn];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        v.clear(); for (int i = 1; i <= m; i++) a[i] = ans[i] = 0;
        scanf("%d", &p);
        for (int i = 1; i <= p; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1++; y1++; x2++; y2++;
            v.push_back({ x2, y2, 1, 0, 0 });
            v.push_back({ x1 - 1, y1 - 1, 1, 0, 0 });
            v.push_back({ x1 - 1, y2, -1, 0, 0 });
            v.push_back({ x2, y1 - 1, -1, 0, 0});
        }
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1++; y1++; x2++; y2++;
            v.push_back({ x2, y2, 1, i, 1 });
            v.push_back({ x1 - 1, y1 - 1, 1, i, 1 });
            v.push_back({ x1 - 1, y2, -1, i, 1 });
            v.push_back({ x2, y1 - 1, -1, i, 1});
        }
        sort(v.begin(), v.end());
        for (Ope& op: v) {
            dbg(op.l, op.r, op.f, op.tp, op.id);
            if (op.tp == 0) {
                // update
                update(1, op.f);
                update(op.r + 1, -op.f);
            } else {
                // query
                ans[op.id] += query(op.r) * op.f;
            }
        }
        for (int i = 1; i <= q; i++) {
            dbg(ans[i]);
        }
    }  
    return 0;
}