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
const int maxn = 100000 + 5;

int n, m, vis[maxn];
string s[maxn];

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  string ans, mid;
  vector<string> ps;
  map<string,int> mp;
  mp[s[0]] = 0;
  for (int i = 1; i < n; i++) {
    string re(s[i]); reverse(begin(re), end(re));
    if (mp.count(re)) {
      vis[mp[re]] = true;
      vis[i] = true;
      ps.push_back(re);
      mp.erase(re);
    } else {
      mp[s[i]] = i;
    }
  }
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;
    string re(s[i]); reverse(begin(re), end(re));
    if (re == s[i]) {
      mid = s[i];
    }
  }
  for (auto x: ps) ans += x;
  ans += mid;
  reverse(begin(ps), end(ps));
  for (auto x: ps) {
    reverse(begin(x), end(x));
    ans += x;
  }
  cout << ans.size() << '\n' << ans << '\n';
  return 0;
}