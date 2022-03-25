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
const int maxn = 200 + 5;

int n;
char s[maxn];

struct Var {
  char id;
  int field = -1;

  Var() {}
  Var(char x, int f = -1) {
    id = x; field = f;
  }

  bool isObj() const {
    if ('a' <= id && id <= 'z') {
      assert(field == -1);
      return true;
    } else {
      return false;
    }
  }
};

struct Code {
  Var lhs, rhs;
} a[maxn];

struct Task {
  int varId;
  vector<int> pts;
};

set<int> Pt[26 * 26 + 5];
set<int> Pfg[26 * 26 + 5];

vector<int> getDelta(int x, const vector<int>& pts) {
  vector<int> ans;
  for (auto& y: pts) {
    if (!Pt[x].count(y)) {
      ans.push_back(y);
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  cin.ignore();
  for (int i = 1; i <= n; i++) {
    cin.getline(s, 200);
    if (s[1] == '.') {
      a[i].lhs = Var(s[0], s[2] - 'a');
      if ('a' <= s[6] && s[6] <= 'z') {
        a[i].rhs = Var(s[6], -1);
      } else {
        if (s[7] == '.') {
          a[i].rhs = Var(s[6], s[8] - 'a');
        } else {
          a[i].rhs = Var(s[6], -1);
        }
      }
    } else {
      a[i].lhs = Var(s[0], -1);
      if ('a' <= s[4] && s[4] <= 'z') {
        a[i].rhs = Var(s[4], -1);
      } else {
        if (s[5] == '.') {
          a[i].rhs = Var(s[4], s[6] - 'a');
        } else {
          a[i].rhs = Var(s[4], -1);
        }
      }
    }
  }

  // for (int i = 1; i <= n; i++) {
  //   dbg(i);
  //   dbg(a[i].lhs.id, a[i].lhs.field);
  //   dbg(a[i].rhs.id, a[i].rhs.field);
  // }

  int tot = 52;
  map<PII,int> mem;
  auto getId = [&](char x, int y = -1) {
    if (y == -1) {
      if ('a' <= x && x <= 'z') {
        return (x - 'a') + 26;
      } else {
        return (x - 'A');
      }
    } else {
      // assert('a' <= x && x <= 'z');
      auto cur = make_pair(x - 'a', y);
      if (mem.count(cur)) {
        return mem[cur];
      } else {
        return mem[cur] = ++tot;
      }
    }
  };

  vector<Task> WL;
  auto adde = [&](int x, int y) { // x, y: varId
    if (Pfg[x].count(y)) return ;
    Pfg[x].insert(y);
    vector<int> pts;
    for (auto& j: Pt[x]) {
      pts.push_back(j);
    }
    if (!pts.empty()) {
      WL.push_back(Task { y, pts });
    }
  };
  auto propagate = [&](int x, const vector<int>& pts) {
    if (pts.empty()) return ;
    for (auto& y: pts) {
      Pt[x].insert(y);
    }
    for (auto& v: Pfg[x]) {
      WL.push_back(Task { v, pts });
    }
  };
  for (int i = 1; i <= n; i++) {
    if (a[i].rhs.isObj()) {
      assert(a[i].lhs.field == -1);
      WL.push_back(Task { getId(a[i].lhs.id), vector<int> { a[i].rhs.id - 'a' } });
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!a[i].rhs.isObj() && a[i].lhs.field == -1 && a[i].rhs.field == -1) {
      assert(a[i].lhs.id >= 'A' && a[i].lhs.id <= 'Z');
      assert(a[i].rhs.id >= 'A' && a[i].rhs.id <= 'Z');
      int L = getId(a[i].rhs.id);
      int R = getId(a[i].lhs.id);
      adde(L, R);
    }
  }
  while (!WL.empty()) {
    auto task = WL.back(); WL.pop_back();
    auto delta = getDelta(task.varId, task.pts);
    propagate(task.varId, delta);
    
    if (task.varId < 26) { // variable
      char var = task.varId + 'A';
      for (int i = 1; i <= n; i++) {
        if (a[i].lhs.field != -1 && a[i].lhs.id == var) {
          for (auto& y: delta) {
            assert(0 <= y && y < 26);
            int L = getId(a[i].rhs.id);
            int R = getId('a' + y, a[i].lhs.field);
            adde(L, R);
          }
        } else if (a[i].rhs.field != -1 && a[i].rhs.id == var) {
          for (auto& y: delta) {
            assert(0 <= y && y < 26);
            int L = getId('a' + y, a[i].rhs.field);
            int R = getId(a[i].lhs.id);
            adde(L, R);
          }
        }
      }
    }
  }

  for (int i = 0; i < 26; i++) {
    cout << char('A' + i) << ": ";
    for (int j: Pt[i]) {
      cout << char(j + 'a');
    }
    cout << '\n';
  }
  return 0;
}