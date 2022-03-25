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
const int maxn = 200 + 5;


int getBit(int x, int n) {
  return (x >> n) & 1;
}

int n, q, k, a[maxn][maxn];

// #define TEST

struct Checker {
  int cnt, a[maxn][maxn];

  void read() {
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
      }
    }
  }

  int ans() {
    int res = 0;
    for (int i = 1; i + 1 <= n; i++) {
      for (int j = 1; j + 1 <= n; j++) {
        if (a[i][j] == 0 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 0) {
          res++;
        }
      }
    }
    return res;
  }

  bool test(int b[maxn][maxn]) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (a[i][j] != b[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  int flip(int x, int y) {
    // dbg(x, y);
    a[x][y] ^= 1;
    cnt++;
    if (cnt > n * n * 4) {
      return -1;
    }
    return ans();
  }

  void print() {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        printf("%d ", a[i][j]);
      }
      puts("");
    }
  }
} chk;

int query(int x, int y) {
  #ifdef TEST
    int r = chk.flip(x, y);
    if (r == -1) exit(0);
    return k = r;
  #else
    printf("1 %d %d\n", x, y);
    fflush(stdout);
    scanf("%d", &x);
    if (x == -1) exit(0);
    return k = x;
  #endif
}

void print() {
  #ifdef TEST
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      printf("%d ", a[i][j]);
    }
    puts("");
  }  
  #endif
}

void solve(int bx, int by) {
  int ex = 1;
  if (bx > 1 && by > 1) {
    if (a[bx - 1][by - 1] == 0 && a[bx - 1][by] == 1 && a[bx][by - 1] == 1) {
      ex++;
    }
  }

  int opt = 0, cur = 0, cnt = 0;
  auto check = [&]() {
    int old = k;
    cur ^= 1;
    query(bx, by);
    if (abs(old - k) == ex) {
      if (k > old) opt = cur;
      else opt = cur ^ 1;
      cnt++;
    }
  };
  auto flip = [&](int x, int y) {
    cur ^= 1 << (x + x + y);
    query(x + bx, y + by);
    check();
  };

  check();
  flip(0, 1);
  flip(1, 0);
  flip(0, 1);
  flip(1, 1);
  flip(1, 0);
  flip(0, 1);
  flip(1, 0);
  assert(cnt == 1);
  
  if (getBit(opt, 0)) {
    a[bx][by] = 1;
  } else {
    a[bx][by] = 0;
  }
  if (!getBit(opt, 1)) {
    a[bx][by + 1] = 0;
  } else {
    a[bx][by + 1] = 1;
  }
  if (!getBit(opt, 2)) {
    a[bx + 1][by] = 0;
  } else {
    a[bx + 1][by] = 1;
  }
  if (!getBit(opt, 3)) {
    query(bx + 1, by + 1);
    a[bx + 1][by + 1] = 0;
  } else {
    a[bx + 1][by + 1] = 0;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    #ifdef TEST
      scanf("%d", &n);
      chk.read();
      k = chk.ans();
    #else
      scanf("%d%d%d", &n, &q, &k);
    #endif
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        a[i][j] = 0;
      }
    }

    for (int i = 2; i <= n; i += 2) {
      for (int j = 2; j <= n; j += 2) {
        solve(i - 1, j - 1);
        // print();
      }
    }

    if (n % 2 == 1) {
      for (int i = 2; i <= n; i += 2) {
        int bx = i - 1, by = n - 1;
        if (a[bx][by] == 1) {
          query(bx, by);
          a[bx][by] ^= 1;
        }
        if (a[bx + 1][by] == 0) {
          query(bx + 1, by);
          a[bx + 1][by] ^= 1;
        }

        a[bx][by + 1] = 1;
        a[bx + 1][by + 1] = 0;

        int old = k;
        query(bx, by + 1);
        if (k == old + 1) continue;
        query(bx + 1, by + 1);
        if (k == old + 1) continue;
        query(bx, by + 1);
        if (k == old + 1) continue;
        query(bx + 1, by + 1);
      }

      for (int j = 2; j <= n; j += 2) {
        int bx = n - 1, by = j - 1;
        if (a[bx][by] == 1) {
          query(bx, by);
          a[bx][by] ^= 1;
        }
        if (a[bx][by + 1] == 0) {
          query(bx, by + 1);
          a[bx][by + 1] ^= 1;
        }

        a[bx + 1][by] = 1;
        a[bx + 1][by + 1] = 0;

        int old = k;
        query(bx + 1, by);
        if (k == old + 1) continue;
        query(bx + 1, by + 1);
        if (k == old + 1) continue;
        query(bx + 1, by);
        if (k == old + 1) continue;
        query(bx + 1, by + 1);
      }

      a[n - 1][n - 1] = 0;
      a[n - 1][n] = 1;
      a[n][n - 1] = 1;

      query(n - 1, n - 1);
      query(n - 1, n);
      query(n, n - 1);

      int old = k;
      query(n, n);
      if (k == old + 1) {
        a[n][n] = 0;
      } else {
        a[n][n] = 1;
      }
    }

    #ifdef TEST
      int r = chk.test(a);
      dbg(r);
      if (!r) {
        print();
        puts("");
        chk.print();
        return 0;
      }
    #else
      puts("2");
      fflush(stdout);
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          printf("%d%c", a[i][j], " \n"[j == n]);
        }
        fflush(stdout);
      }
      fflush(stdout);
      int ans;
      scanf("%d", &ans);
      if (ans == -1) {
        return 0;
      }
    #endif
  }
  return 0;
}