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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 4005 + 5;

char tmp[300];
string code[maxn];
vector<int> b1, b2;
int n, dp[maxn][maxn][4];

tuple<int,int,int> getpre(int i, int j, int st) {
  auto noans = make_tuple(-1, -1, -1);
  if (i == 0 && j == 0) return noans;
  if (st == 0) {
    if (dp[i][j][0] + 1 == dp[i + 1][j + 1][0]) {
      return make_tuple(i, j, 0);
    } else if (dp[i][j][1] + 1 == dp[i + 1][j + 1][0]) {
      return make_tuple(i, j, 1);
    } else if (dp[i][j][2] + 1 == dp[i + 1][j + 1][0]) {
      return make_tuple(i, j, 2);
    } else if (dp[i][j][3] + 1 == dp[i + 1][j + 1][0]) {
      return make_tuple(i, j, 3);
    }
  } else if (st == 1) {
    if (dp[i][j][0] + 5 == dp[i + 1][j + 1][1]) {
      return make_tuple(i, j, 0);
    } else if (dp[i][j][2] + 5 == dp[i + 1][j + 1][1]) {
      return make_tuple(i, j, 2);
    } else if (dp[i][j][3] + 5 == dp[i + 1][j + 1][1]) {
      return make_tuple(i, j, 3);
    } else if (dp[i][j][1] + 2 == dp[i + 1][j + 1][1]) {
      return make_tuple(i, j, 1);
    } else if (dp[i + 1][j][1] + 1 == dp[i + 1][j + 1][1]) {
      return make_tuple(i + 1, j, 1);
    } else if (dp[i][j + 1][1] + 1 == dp[i + 1][j + 1][1]) {
      return make_tuple(i, j + 1, 1);
    }
  } else if (st == 2) {
    if (dp[i][j + 1][0] + 3 == dp[i + 1][j + 1][2]) {
      return make_tuple(i, j + 1, 0);
    } else if (dp[i][j + 1][1] + 3 == dp[i + 1][j + 1][2]) {
      return make_tuple(i, j + 1, 1);
    } else if (dp[i][j + 1][3] + 3 == dp[i + 1][j + 1][2]) {
      return make_tuple(i, j + 1, 3);
    } else if (dp[i][j + 1][2] + 1 == dp[i + 1][j + 1][2]) {
      return make_tuple(i, j + 1, 2);
    }
  } else if (st == 3) {
    if (dp[i + 1][j][0] + 3 == dp[i + 1][j + 1][3]) {
      return make_tuple(i + 1, j, 0);
    } else if (dp[i + 1][j][1] + 3 == dp[i + 1][j + 1][3]) {
      return make_tuple(i + 1, j, 1);
    } else if (dp[i + 1][j][2] + 3 == dp[i + 1][j + 1][3]) {
      return make_tuple(i + 1, j, 2);
    } else if (dp[i + 1][j][3] + 1 == dp[i + 1][j + 1][3]) {
      return make_tuple(i + 1, j, 3);
    }
  }
  return noans;
}

int main() {
  int state = 0;
  while (cin.getline(tmp, 300)) {
    code[++n] = string(tmp);
    if (code[n].substr(0, 15) == "<<<<<<< branch1") {
      state = 1;
    } else if (code[n].substr(0, 7) == "=======") {
      state = 2;
    } else if (code[n].substr(0, 15) == ">>>>>>> branch2") {
      state = 0;
    } else {
      if (state == 0) {
        b1.push_back(n);
        b2.push_back(n);
      } else if (state == 1) {
        b1.push_back(n);
      } else if (state == 2) {
        b2.push_back(n);
      }
    }
  }
  
  for (int i = 0; i <= (int)b1.size(); i++) {
    for (int j = 0; j <= (int)b2.size(); j++) {
      dp[i][j][0] = dp[i][j][1] = n * 100;
      dp[i][j][2] = dp[i][j][3] = n * 100;
    }
  }
  dp[0][0][0] = 0;
  for (int i = 1; i <= (int)b1.size(); i++) {
    dp[i][0][1] = i + 3;
    dp[i][0][2] = i + 2;
  }
  for (int j = 1; j <= (int)b2.size(); j++) {
    dp[0][j][1] = j + 3;
    dp[0][j][3] = j + 2;
  }
  for (int i = 0; i < (int)b1.size(); i++) {
    for (int j = 0; j < (int)b2.size(); j++) {
      if (b1[i] == b2[j] || code[b1[i]] == code[b2[j]]) {
        dp[i + 1][j + 1][0] = min(min(dp[i][j][0], dp[i][j][1]), min(dp[i][j][2], dp[i][j][3])) + 1;
      } else {
        dp[i + 1][j + 1][0] = n * 100;
      }
      {
        dp[i + 1][j + 1][1] = min(min(dp[i][j][0], min(dp[i][j][2], dp[i][j][3])) + 5, dp[i][j][1] + 2);
        dp[i + 1][j + 1][1] = min(dp[i + 1][j + 1][1], dp[i + 1][j][1] + 1);
        dp[i + 1][j + 1][1] = min(dp[i + 1][j + 1][1], dp[i][j + 1][1] + 1);
      }
      {
        dp[i + 1][j + 1][2] = min(min(dp[i][j + 1][0], min(dp[i][j + 1][1], dp[i][j + 1][3])) + 3, dp[i][j + 1][2] + 1);
      }
      {
        dp[i + 1][j + 1][3] = min(min(dp[i + 1][j][0], min(dp[i + 1][j][1], dp[i + 1][j][2])) + 3, dp[i + 1][j][3] + 1);
      }
      dbg(i, j, dp[i + 1][j + 1][0], dp[i + 1][j + 1][1], dp[i + 1][j + 1][2], dp[i + 1][j + 1][3]);
    }
  }
  int x = b1.size(), y = b2.size(), st = 0;
  int mn = min(min(dp[x][y][0], dp[x][y][1]), min(dp[x][y][2], dp[x][y][3]));
  if (dp[x][y][1] == mn) {
    st = 1;
  } else if (dp[x][y][2] == mn) {
    st = 2;
  } else if (dp[x][y][3] == mn) {
    st = 3;
  }
  dbg(dp[x][y][0], dp[x][y][1], dp[x][y][2], dp[x][y][3]);
  vector<string> ans;
  while (x >= 0 && y >= 0) {
    if (x == 0 && y == 0) break;
    vector<PII> vec;
    while (get<2>(getpre(x - 1, y - 1, st)) == st) {
      vec.emplace_back(x, y);
      auto pre = getpre(x - 1, y - 1, st);
      int nx = get<0>(pre);
      int ny = get<1>(pre);
      x = nx;
      y = ny;
    }
    vec.emplace_back(x, y);
    dbg(x, y, st);
    if (st == 0) {
      for (auto& x: vec) {
        assert(x.first >= 1);
        ans.push_back(code[b1[x.first - 1]]);
      }
    } else if (st == 1) {
      ans.push_back("#endif");
      int last = -1;
      for (auto& x: vec) {
        if (x.second != last) {
          assert(x.second >= 1);
          ans.push_back(code[b2[x.second - 1]]);
          last = x.second;
        }
      }
      ans.push_back("#else");
      last = -1;
      for (auto& x: vec) {
        if (x.first != last) {
          assert(x.first >= 1);
          ans.push_back(code[b1[x.first - 1]]);
          last = x.first;
        }
      }
      ans.push_back("#ifdef branch1");
    } else if (st == 2) {
      ans.push_back("#endif");
      for (auto& x: vec) {
        assert(x.first >= 1);
        ans.push_back(code[b1[x.first - 1]]);
      }
      ans.push_back("#ifdef branch1");
    } else if (st == 3) {
      ans.push_back("#endif");
      for (auto& x: vec) {
        assert(x.second >= 1);
        ans.push_back(code[b2[x.second - 1]]);
      }
      ans.push_back("#ifdef branch2");
    }

    auto pre = getpre(x - 1, y - 1, st);
    int nx = get<0>(pre);
    int ny = get<1>(pre);
    int ns = get<2>(pre);
    x = nx;
    y = ny;
    st = ns;
    dbg(nx, ny, ns);
  }
  dbg("OK");
  reverse(begin(ans), end(ans));
  for (auto& x: ans) {
    cout << x << '\n';
  }
  return 0;
}