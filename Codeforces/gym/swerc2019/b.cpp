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
const int maxn = 200000 + 5;

int n;

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  map<string,int> mp;
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    mp[s]++;
  }
  for (auto& x: mp) {
    if (x.second > n - x.second) {
      cout << x.first << endl;
      return 0;
    }
  }
  cout << "NONE" << endl;
  return 0;
}