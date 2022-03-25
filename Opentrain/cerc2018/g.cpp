#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxy = 100000 + 5;
const int maxx = 50 + 5;

int pre[maxx * maxy], mp[maxx][maxy];
int id(int x, int y) {
    // (x, y) => x * maxy + y;
    return x * maxy + y;
}
int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return ;
    pre[x] = y;
}

struct DSU {
    int pre[maxy], ri[maxy], vis[maxy];
    DSU() {
        for (int i = 1; i < maxy; i++) {
            pre[i] = ri[i] = i;
        }
    }
    int find(int x) {
        return x == pre[x] ? x : pre[x] = find(pre[x]);
    }
    int nxt(int p) {
        if (vis[p]) return ri[find(p)] + 1;
        return p;
    }
    void join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return ;
        pre[x] = y; ri[y] = max(ri[y], ri[x]);
    }
} h[maxx];

void link(int x, int y1, int y2) {
    int tot = h[x].nxt(y1);
    while (tot <= y2) {
        h[x].vis[tot] = 1;
        mp[x][tot] = 1;
        if (mp[x][tot - 1]) join(id(x, tot), id(x, tot - 1)), h[x].join(tot, tot - 1);
        if (mp[x][tot + 1]) join(id(x, tot), id(x, tot + 1)), h[x].join(tot, tot + 1);
        if (mp[x - 1][tot]) join(id(x, tot), id(x - 1, tot));
        if (mp[x + 1][tot]) join(id(x, tot), id(x + 1, tot));
        tot = h[x].nxt(tot);
    }
}

int main() {
    for (int i = 1; i < maxx * maxy; i++) pre[i] = i;
    int q, op, x1, x2, y1, y2; scanf("%d", &q);
    for (int T = 1; T <= q; T++) {
        scanf("%d%d%d%d%d", &op, &x1, &y1, &x2, &y2);
        if (op == 0) {
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            for (int i = x1; i <= x2; i++) link(i, y1, y2);
        } else if (op == 1) {
            if (mp[x1][y1] && find(id(x1, y1)) == find(id(x2, y2))) puts("1");
            else puts("0");
        }
    }
    return 0;
}