#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#ifdef XLor
#define dbg(args...) cout << #args << " -> ", err(args)

void err() { std::cout << std::endl; }

template <typename T, typename... Args>
void err(T a, Args... args) {
  std::cout << a << ' ';
  err(args...);
}

#else
#define dbg(...)
#endif
using ll = long long;
using namespace std;
const int N = 3e5 + 10;
const int Mod = 1e9 + 7;
const long double eps = 1e-10;
const int dx[] = {0, 1, -1, -1, 1};
const int dy[] = {0, 1, 1, -1, -1};
int opt = 0;
int flag = 0;

struct Point {
  int x, y;
};
Point p1 = {0, -237};
long double query(int x0, int y0, int xd, int yd) {
  #ifdef XLor
    long double P = 1,R = (x0 - p1.x) * (x0 - p1.x) + (y0 - p1.y) * (y0 - p1.y);
    if (abs(R) < eps) {
      //  dbg(x0,y0);
      puts("YES");
      exit(0);
    }
    long double fi = (x0 - p1.x) * (0 - xd) + (y0 - p1.y) * (0 - yd);
    if(fi < -eps) {
      return 0;
    }
    fi = fi/(sqrt(R) * sqrt((0 - xd) * (0 - xd) + (0 - yd) * (0 -  yd)));
    long double Ans = fi * P / R;
    return fi * P / R;
  #else
    cout << "? " << x0 << " " << y0 << " " << xd << " " << yd << endl;
    long double x;
    cin >> x;
    if (x < (-eps)) {
      exit(0);
    }
    return x;
  #endif
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  #ifdef XLor
    cin >> p1.x >> p1.y;
  #endif

  long double x1 = query(0, 0, 1, 0), y1 = query(0, 0, 0, 1);
  if (x1 > 0 && y1 > 0)
    opt = 1;
  else if (x1 > 0)
    opt = 4;
  else if (y1 > 0)
    opt = 2;
  else
    opt = 3;
  // dbg(opt);
  x1 = query(0, 0, dx[opt], 0);
  y1 = query(0, 0, 0, dy[opt]);
  if ((x1) < eps) {
    int x = 0, y = dy[opt];
    x1 = query(0, 0, 0, y);
    y1 = query(0, y, 0, y);
    double del = sqrt(x1 * y1);
    double k1 = (y1 - del) / (y1 - x1), k2 = (y1 + del) / (y1 - x1);
    query(k1 * x, k1 * y, x, y);
    query(k2 * x, k2 * y, x, y);
    return 0;
  }
  int x = 0, y = 0;
  for (int i = 1; i <= 1000; i++) {
    int hhh = 0;
    for (int j = 0; j <= 1000; j++) {
      long double fz = j, fm = i;
      if (abs(fz * x1 - fm * y1) <= eps) {
        x = i * dx[opt];
        y = j * dy[opt];
        hhh = 1;
        break;
      }
    }
    if (hhh) break;
  }
  int d = __gcd(abs(x), abs(y));
  x /= d, y /= d;
  x1 = query(0, 0, x, y);
  y1 = query(x, y, x, y);
  double del = sqrt(x1 * y1);
  double k1 = (y1 - del) / (y1 - x1), k2 = (y1 + del) / (y1 - x1);
  query(k1 * x, k1 * y, x, y);
  query(k2 * x, k2 * y, x, y);
}