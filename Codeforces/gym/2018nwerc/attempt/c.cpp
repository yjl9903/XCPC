#include <bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define inf 0x3f3f3f3f
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repp(i, a, b) for (int i = a; i <= b; i++)
#define rep1(i, a, b) for (int i = a; i >= b; i--)
#define mem(gv) memset(gv, 0, sizeof(gv))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define QAQ 0
#ifdef XLor
#define dbg(args...)        \
  do {                      \
    cout << #args << " : "; \
    err(args);              \
  } while (0)
void err() { std::cout << std::endl; }
template <typename T, typename... Args>
void err(T a, Args... args) {
  std::cout << a << ' ';
  err(args...);
}
#else
#define dbg(...)
#endif

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pLL;
const ll mod = 1e9 + 7;
const int maxn = 2e5 + 22;
const double pi = acos(-1.0);

int n, a, b, from[maxn], to[maxn], dep[maxn];
vector<int> v[maxn];
struct node {
  double l, r, x, y;

  double distance(node b) const {
    double x = this->x - b.x;
    double y = this->y - b.y;
    return hypot(x, y);
  }
} c[maxn];

int rt = 1;
void dfs(int u, int fa) {
  int sz = (int)v[u].size() - 1;
  if (u == rt) sz++;
  if (!sz) return;
  
  double k = (c[u].r - c[u].l) / sz;
  // dbg(u, sz, dep[u], c[u].r - c[u].l, k);
   dbg(u,c[u].l,c[u].r);
  int cnt = 0;
  for (auto x : v[u]) {
    if (x == fa) continue;
    ++cnt;
    double tl = c[u].l + (cnt - 1) * k, tr = c[u].l + cnt * k;
    // if (cnt == 1) tl = c[u].l;
    // if (cnt == sz) tr = c[u].r;
    c[x].l = tl;
    c[x].r = tr;
    double ang = (tl + tr) / 2;
    c[x].x = c[u].x + 1.0 * sin(ang);
    c[x].y = c[u].y + 1.0 * cos(ang);

    dep[x] = dep[u] + 1;
    dfs(x, u);
  }
}

int main() {
  srand(time(nullptr));
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
    from[i] = a;
    to[i] = b;
  }

  rt = 1;
  c[rt].l = 0.0;
  c[rt].r = 2.0 * pi;
  c[rt].x = c[rt].y = 0.0;
  dfs(rt, -1);

  double r = inf;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      r = min(r, c[i].distance(c[j]));
      assert(abs(c[i].distance(c[j])) > 1e-4);
    }
  }
  dbg(r);

  // for (int i = 1; i <= n; i++) {
  //   printf("%.8lf %.8lf\n", c[i].x, c[i].y);
  // }

  return 0;
}