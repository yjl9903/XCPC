#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int maxv = 1e9;
const int maxn = 400000 + 5;

int n, ql[maxn], qr[maxn];

struct node {
    int l, r;
    mutable ll v;
    node(int L, int R = -1, ll V = 0): l(L), r(R), v(V) { }
    bool operator<(const node& o) const {
        return l < o.l;
    }
};
set<node> s;
using IT = set<node>::iterator;
IT split(int pos) {
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) 
        return it;
    it--;
    int L = it->l, R = it->r;
    ll V = it->v;
    s.erase(it);
    s.insert(node(L, pos - 1, V));
    return s.insert(node(pos, R, V)).first;
}
void add(int l, int r) {
    IT itr = split(r + 1),itl = split(l);
    for (; itl != itr; ++itl) 
        itl->v++;
}
ll query(int l, int r, ll k) {
    IT itr = split(r + 1), itl = split(l);
    for (; itl != itr; itl++) {
        ll sum = itl->v * (itl-> r - itl-> l + 1);
        if (k > sum) k -= sum;
        else {
            ll now = k / itl->v; if (k % itl->v) now++;
            return itl->l + now - 1;
        }
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    int x1, x2, a1, b1, c1, m1;
    int y1, y2, a2, b2, c2, m2;
    scanf("%d%d%d%d%d%d", &x1, &x2, &a1, &b1, &c1, &m1);
    scanf("%d%d%d%d%d%d", &y1, &y2, &a2, &b2, &c2, &m2);
    ql[1] = min(x1, y1) + 1;
    qr[1] = max(x1, y1) + 1;
    ql[2] = min(x2, y2) + 1;
    qr[2] = max(x2, y2) + 1;
    for (int i = 3; i <= n; i++) {
        int nx = (1ll * a1 * x2 + 1ll * b1 * x1 + c1) % m1;
        int ny = (1ll * a2 * y2 + 1ll * b2 * y1 + c2) % m2;
        ql[i] = min(nx, ny) + 1;
        qr[i] = max(nx, ny) + 1;
        x1 = x2; x2 = nx;
        y1 = y2; y2 = ny;
    }
    ll all = 0;
    s.insert({maxv + 1, maxv + 1, 0});
    for (int i = 1; i <= n; i++) {
        // dbg(ql[i], qr[i]);
        add(ql[i], qr[i]);
        all += qr[i] - ql[i] + 1;
        ll target = (all + 1ll) / 2ll;
        printf("%lld\n", query(1, maxv, target));
    }
    return 0;
}