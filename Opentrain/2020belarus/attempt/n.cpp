#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

struct LinearFunction {
  int k, b;

  LinearFunction(int x) : k(0), b(x) {}
  LinearFunction(int k, int b) : k(k), b(b) {}

  int operator()(int x) {
    return k * x + b;
  }
};

struct SegT {
  int l, r, mid;
  SegT *lc, *rc;
  LinearFunction f;

  SegT(int l, int r, SegT *lc, SegT *rc) : l(l), r(r), mid(l + (r - l) / 2), lc(lc), rc(rc), f(INT_MAX) {}

  int query(int pos) {
    if (l == r) return f(pos);
    else return std::min(f(pos), (pos > mid ? rc : lc)->query(pos));
  }

  void cover(LinearFunction f) {
    if (f(mid) < this->f(mid)) std::swap(f, this->f);
    if (f(l) < this->f(l)) lc->cover(f);
    if (f(r) < this->f(r)) rc->cover(f);
  }

  void update(int ql, int qr, const LinearFunction &f) {
    if (ql > r || qr < l) return;
    else if (ql <= l && qr >= r) cover(f);
    else lc->update(ql, qr, f), rc->update(ql, qr, f);;
  }

  static SegT *build(int l, int r) {
    if (l == r) return new SegT(l, r, NULL, NULL);
    else {
      int mid = l + (r - l) / 2;
      return new SegT(l, r, build(l, mid), build(mid + 1, r));
    }
  }
};

int n, a[maxn], ok[maxn], L[maxn], R[maxn];

int main() {
  scanf("%d", &n);
  vector<int> vec;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    vec.push_back(i);
    rest[i] = inf;
  }
  sort(vec.begin(), vec.end(), [&](int x, int y) {
    return a[x] > a[y];
  });
  SegT *seg = SegT::build(1, n);
  set<int> vis, ans;
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && a[vec[i]] == a[vec[j]]) {
      j++;
    }
    if (i == 0) {
      for (int k = i; k < j; k++) {
        int id = vec[k];
        ans.insert(id);
        vis.insert(id);

      }
    } else {

    }
  }
  printf("%d\n", ans.size());
  for (int x: ans) printf("%d ", x);
  return 0;
}