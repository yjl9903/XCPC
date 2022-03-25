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

set<pair<string,string> > egs;

vector<string> trans(const string& s) {
  vector<string> near;

  int id = s.find("00");
  while (id != -1) {
    string nx = s;
    nx[id] = '1'; nx[id + 1] = '2';
    near.push_back(nx);
    id = s.find("00", id + 1);
  }

  id = s.find("12");
  while (id != -1) {
    string nx = s;
    nx[id] = '0'; nx[id + 1] = '0';
    near.push_back(nx);
    id = s.find("12", id + 1);
  }

  id = s.find("111");
  while (id != -1) {
    string nx = s;
    nx.erase(begin(nx) + id);
    nx[id] = '2'; nx[id + 1] = '0';
    near.push_back(nx);
    id = s.find("111", id + 1);
  }

  id = s.find("20");
  while (id != -1) {
    string nx = s;
    nx[id] = '1'; nx[id + 1] = '1';
    nx.insert(begin(nx) + id, '1');
    near.push_back(nx);
    id = s.find("20", id + 1);
  }

  id = s.find("22");
  while (id != -1) {
    string nx = s;
    nx.erase(begin(nx) + id, begin(nx) + id + 2);
    near.push_back(nx);
    id = s.find("22", id + 1);
  }

  id = s.find("012");
  while (id != -1) {
    string nx = s;
    nx.erase(begin(nx) + id, begin(nx) + id + 3);
    near.push_back(nx);
    id = s.find("012", id + 1);
  }

  return near;
}

int main() {
  auto v = trans("0122");
  for (auto& x: v) {
    dbg(x);
  }
  return 0;
}