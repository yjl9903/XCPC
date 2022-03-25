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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n, step, ok =false, mp[20][20];

struct Car {
  vector<PII> vec;
  void print() const {
    for (auto& x: vec) printf("(%d, %d) ", x.first, x.second);
    puts("");
  }
  int dis() const {
    return abs(vec[0].first - 3) + abs(vec[0].second - 5);
  }
  bool check(const Car& car) {
    for (auto& x: vec) {
      for (auto& y: car.vec) {
        if (x == y) return false;
      }
    }
    return true;
  }
  bool move(PII d, int me, const vector<Car>& cars) {
    bool flag = true;
    for (auto& x: vec) {
      x.first += d.first;
      x.second += d.second;
      if (x.first < 1 || x.first > 6) flag = false;
      if (x.second < 1 || x.second > 6) flag = false;
    }
    if (vec[0].first == vec[1].first) {
      if (d.first) return false;
    } else {
      if (d.second) return false;
    }
    if (!flag) return false;
    for (int i = 0; i < (int)cars.size(); i++) {
      if (i == me) continue;
      if (!check(cars[i])) {
        return false;
      }
    }
    return true;
  }
  void reset(PII d) {
    for (auto& x: vec) {
      x.first -= d.first;
      x.second -= d.second;
    }
  }
} a[20];

void dfs(const vector<Car>& cars, int tot) {
  if (ok) return ;
  int d = cars[0].dis();
  if (d == 0) {
    ok = true; return ;
  }
  if (tot + d > step) return ;
  auto now = cars;
  for (int i = 0; i < (int)cars.size(); i++) {
    for (auto d: dir) {
      if (now[i].move(d, i, cars)) {
        dfs(now, tot + 1);
      }
      now[i].reset(d);
    }
  }
}

int main() {
  for (int i = 1; i <= 6; i++) {
    for (int j = 1; j <= 6; j++) {
      int x; scanf("%d", &x);
      mp[i][j] = x;
      a[x].vec.push_back({ i, j });
    }
  }
  if (a[1].vec[0].second == a[1].vec[1].second) {
    puts("-1");
    return 0;
  }
  vector<Car> cars;
  for (int i = 1; i <= 10; i++) {
    if (!a[i].vec.empty()) {
      cars.push_back(a[i]);
    }
  }
  int ans = -3;
  for (step = 0; step <= 8 && ans == -3; step++) {
    ok = false;
    dfs(cars, 0);
    if (ok) {
      ans = step;
    }
  }
  printf("%d\n", ans + 2);
  return 0;
}