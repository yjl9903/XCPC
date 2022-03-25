#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, m, a[maxn], mn[maxn << 2], tag[maxn << 2];
PII p[maxn];
vector<int> mk[maxn];

void pushup(int rt) {
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void pushdown(int rt) {
    if (!tag[rt]) return;
    mn[rt << 1] += tag[rt]; mn[rt << 1 | 1] += tag[rt];
    tag[rt << 1] += tag[rt]; tag[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    if (l == r) {
        mn[rt] = a[l]; return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        mn[rt] += x; tag[rt] += x;
        return;
    }
    int m = l + r >> 1; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int i, int l, int r, int rt) {
    if (l == r) return mn[rt];
    int m  = l + r >> 1; pushdown(rt);
    if (i <= m) return query(i, lson);
    else return query(i, rson);
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
        mk[p[i].first].push_back(p[i].second);
        update(p[i].first, p[i].second, -1, 1, n, 1);
    }
    int ans = 0, ansp = 1, l = 1, r = 0;
    priority_queue<PII, vector<PII>, greater<PII> > pq;
    for (int i = 1; i <= n; i++) {
        while (!pq.empty()) {
            PII t = pq.top();
            if (t.first < i) {
                pq.pop(); update(t.second, t.first, -1, 1, n, 1);
            } else break;
        }
        for (int& x: mk[i]) {
            pq.push({x, i}); update(i, x, 1, 1, n, 1);
        }
        int t = query(i, 1, n, 1) - mn[1];
        if (ans < t) ans = t, ansp = i;
    }
    printf("%d\n", ans);
    vector<int> v;
    for (int i = 1; i <= m; i++) {
        if (ansp > p[i].second || ansp < p[i].first) v.push_back(i);
    }
    printf("%d\n", v.size()); for (int& x: v) printf("%d ", x);
    return 0;
}