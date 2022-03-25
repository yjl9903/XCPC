#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int pre[maxn << 1], siz[maxn << 1], xcnt[maxn << 1], ycnt[maxn << 1];
int find(int x) {
    while (x != pre[x]) x = pre[x]; return x;
}
ll sum = 0;
vector<PII> sta;
bool join(int x, int y) {
    // dbg(x, y);
    x = find(x); y = find(y);
    if (x == y) return 0;
    sum -= 1ll * xcnt[x] * ycnt[x]; sum -= 1ll * xcnt[y] * ycnt[y];
    if (siz[x] > siz[y]) swap(x, y);
    pre[x] = y; siz[y] += siz[x];
    xcnt[y] += xcnt[x]; ycnt[y] += ycnt[x];
    sum += 1ll * xcnt[y] * ycnt[y];
    sta.push_back({x, y});
    return 1;
}
void undo() {
    PII tp = sta.back(); sta.pop_back();
    int x = tp.first, y = tp.second;
    pre[x] = x; siz[y] -= siz[x];
    sum -= 1ll * xcnt[y] * ycnt[y];
    xcnt[y] -= xcnt[x]; ycnt[y] -= ycnt[x];
    sum += 1ll * xcnt[x] * ycnt[x]; sum += 1ll * xcnt[y] * ycnt[y];
}

vector<PII> nodes[maxn << 2];
void update(int L, int R, PII x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        nodes[rt].push_back(x); return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
}

ll ans[maxn];
void solve(int l, int r, int rt) {
    int cnt = 0;
    // dbg(l, r);
    // for (auto& x: nodes[rt]) dbg(x.first, x.second);
    for (auto& x: nodes[rt]) if (join(x.first, x.second)) cnt++;
    if (l == r) {
        ans[l] = sum;
        for (int i = 0; i < cnt; i++) undo();
        return ;
    }
    int m = (l + r) >> 1;
    solve(lson); solve(rson);
    for (int i = 0; i < cnt; i++) undo();
}

int n, x[maxn], y[maxn]; 
map<PII,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) {
        pre[i] = i; siz[i] = 1;
        xcnt[i] = (i <= n); ycnt[i] = (i > n);
    }
    vector<int> xx, yy;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", x + i, y + i);
        xx.push_back(x[i]); yy.push_back(y[i]);
    }
    sort(xx.begin(), xx.end()); sort(yy.begin(), yy.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());
    for (int i = 1; i <= n; i++) {
        x[i] = lower_bound(xx.begin(), xx.end(), x[i]) - xx.begin() + 1;
        y[i] = lower_bound(yy.begin(), yy.end(), y[i]) - yy.begin() + 1 + n;
    }
    for (int i = 1; i <= n; i++) {
        if (!mp.count({x[i], y[i]}) || mp[{x[i], y[i]}] <= 0) mp[{x[i], y[i]}] = i;
        else {
            update(mp[{x[i], y[i]}], i - 1, {x[i], y[i]}, 1, n, 1);
            mp[{x[i], y[i]}] = -1;
        }
    }
    for (auto& x: mp) if (x.second > 0) update(x.second, n, x.first, 1, n, 1);
    solve(1, n, 1);
    for (int i = 1; i <= n; i++) printf("%I64d ", ans[i]);
    return 0;
}