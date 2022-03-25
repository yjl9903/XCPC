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
const int maxn = 10000000 + 5;

int n, vis[maxn];

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    if (s[0] == '-') {
      continue;
    }
    if (s.length() >= 7) continue;
    if (atoi(s.c_str()) < maxn) {
      vis[atoi(s.c_str())]++;
    }
  }
  for (int i = 0; i < maxn; i++) {
    if (!vis[i]) {
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}