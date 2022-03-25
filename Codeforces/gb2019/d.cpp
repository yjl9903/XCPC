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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, a[maxn];

PII query(const set<int>& v) {
  assert((int)v.size() == k);
  cout << "?";
  for (int x: v) cout << " " << x;
  cout << endl;
  int x, y; cin >> x >> y;
  return make_pair(x, y);
}

int main() {
  cin >> n >> k;
  if (k == 1) {
    cout << "! 1" << endl;
    return 0;
  }
  set<int> v;
  for (int i = 1; i <= k + 1; i++) v.insert(i);
  map<int,int> mp;
  for (int i = 1; i <= k + 1; i++) {
    v.erase(i);
    auto res = query(v);
    mp[res.second]++;
    v.insert(i);
  }
  assert((int)mp.size() == 2);
  cout << "! " << (mp.rbegin()->second) << endl;
  return 0;
}