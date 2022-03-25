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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
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
using namespace __gnu_pbds;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;
map<string,PII> var;
set<PII> mem;
char s[100];

int add(int size) {
  for (auto& x: mem) {
    if (x.second >= size) {
      int st = x.first, sz = x.second;
      auto it = mem.find({ st, sz });
      assert(it != mem.end());
      mem.erase(it);
      if (sz > size) {
        mem.insert({ st + size, sz - size });
      }
      return st;
    }
  }
  return -1;
}
void del(int pos, int size) {
  int np = pos, ns = size;
  assert(mem.find({ pos, size }) == mem.end());
  auto it = mem.lower_bound({ pos, size });
  auto itL = it, itR = it;
  if (itL != mem.begin()) {
    itL--;
    if (itL->first + itL->second == pos) {
      np -= itL->second; ns += itL->second;
      mem.erase(itL);
    }
  }
  if (itR != mem.end()) {
    if (np + ns == itR->first) {
      ns += itR->second;
      mem.erase(itR);
    }
  }
  // dbg(np, ns);
  mem.insert({ np, ns });
}

int main() {
  scanf("%d", &n);
  mem.insert({ 1, (int)1e5 });
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    string cmd(s);
    if (cmd.find('=') != string::npos) {
      string name = cmd.substr(0, cmd.find('='));
      assert(name.size() == 4);
      int size = atoi(cmd.substr(11, cmd.length() - 13).c_str());
      // dbg(size);
      int pos = add(size);
      if (pos != -1) {
        var[name] = { pos, size };
      } else if (var.count(name)) {
        var.erase(name);
      }
    } else if (cmd[0] == 'f') {
      string name = cmd.substr(5, cmd.length() -  7);
      assert(name.size() == 4);
      // dbg(name);
      if (var.count(name)) {
        del(var[name].first, var[name].second);
        var.erase(name);
      }
    } else if (cmd[0] == 'o') {
      string name = cmd.substr(7, cmd.length() -  9);
      assert(name.size() == 4);
      // dbg(name);
      if (var.count(name)) {
        printf("%d\n", var[name].first);
      } else {
        puts("0");
      }
    }
  }
  return 0;
}