#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 10000 + 5;
const double inf = 1e13 + 7;
const double eps = 1e-8;
const double pi = acos(-1.0);

struct Point {
  ll x, y;

  void read() {
    int a, b;
    scanf("%d%d", &a, &b);
    x = a;
    y = b;
  }

  Point operator+(const Point& b) const { return Point{x + b.x, y + b.y}; }
  Point operator-(const Point& b) const { return Point{x - b.x, y - b.y}; }
} a[maxn], lx[maxn], ly[maxn];

ll cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
ll cross(const Point& a, const Point& b, const Point& c) {
  return cross(b - a, c - a);
}

bool inMid(ll L, ll R, ll x) {
  if (L > R) swap(L, R);
  return L <= x && x <= R;
}

bool check(const Point& q, const Point& lx, const Point& ly) {
  return cross(q - lx, ly - lx) == 0 && inMid(lx.x, ly.x, q.x) &&
         inMid(lx.y, ly.y, q.y);
}

double getPos(const Point& a, const Point& b) {
  double fz = a.y * b.x - a.x * b.y;
  double fm = a.y - b.y;
  return fz / fm;
}

struct Node {
  double pos;
  int id, tp;

  bool operator<(const Node& b) const { return pos < b.pos; }
};

int n, m, vis[maxn];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      a[i].read();
      vis[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
      lx[i].read();
      ly[i].read();
      if (lx[i].y > ly[i].y) swap(lx[i], ly[i]);
    }
    vector<Node> evs;
    auto add = [&](int i, double L, double R) {
      evs.push_back({L, i, 1});
      evs.push_back({R, i, -1});
    };
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (check(a[i], lx[j], ly[j])) {
          add(i, -inf, inf);
        } else if (a[i].y <= lx[j].y) {
          //
        } else if (a[i].y <= ly[j].y) {
          assert(a[i].y != lx[j].y);
          double pos = getPos(a[i], lx[j]);
          ll r = cross(lx[j], ly[j], a[i]);
          if (r > 0) {
            add(i, pos, inf);
          } else if (r < 0) {
            add(i, -inf, pos);
          } else {
            assert(false);
          }
        } else {
          double posX = getPos(a[i], lx[j]);
          double posY = getPos(a[i], ly[j]);
          if (posX > posY) swap(posX, posY);
          add(i, posX, posY);
        }
      }
    }

    sort(begin(evs), end(evs));
    int cur = 0;
    double ans = 0;
    for (int i = 0, j = 0; i < evs.size(); i = j) {
      while (j < evs.size() && evs[j].pos - evs[i].pos < eps) {
        int id = evs[j].id;
        int tp = evs[j].tp;
        if (tp == 1) {
          vis[id]++;
          if (vis[id] == 1) cur++;
        } else if (tp == -1) {
          vis[id]--;
          if (vis[id] == 0) cur--;
        }
        j++;
      }
      if (cur == n) {
        ans += evs[j].pos - evs[i].pos;
      }
    }
    if (ans > 1e9) {
      puts("-1");
    } else {
      printf("%.12lf\n", ans);
    }
  }
  return 0;
}
