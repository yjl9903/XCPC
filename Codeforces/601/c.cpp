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
const int maxn = 1000 + 5;

ll qs(int i, int j, int k) {
  cout << 1 << ' ' << i << ' ' << j << ' ' << k << endl;
  ll sum; cin >> sum; return sum;
}
int qd(int i, int j, int k) {
  cout << 2 << ' ' << i << ' ' << j << ' ' << k << endl;
  cin >> i; return i;
}

int n, dir[maxn];

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  int eg = 2;
  // find an edge
  for (int i = 3; i <= n; i++) {
    int d = qd(1, eg, i);
    if (d > 0) eg = i;
  }

  // sort all the tri
  vector< pair<ll,int> > v;
  for (int i = 2; i <= n; i++) {
    if (i == eg) continue;
    v.emplace_back(qs(1, eg, i), i);
  }
  sort(begin(v), end(v));

  // left or right
  int mxe = v.back().second;
  for (int i = 2; i <= n; i++) {
    if (i == mxe) continue;
    dir[i] = qd(1, mxe, i);
  }

  vector<int> ans1, ans2;
  for (auto& x: v) {
    int i = x.second;
    if (dir[i] > 0) {
      ans1.push_back(i);
    } else if (dir[i] < 0) {
      ans2.push_back(i);
    }
  }
  vector<int> ans(1, 1);
  for (int x: ans2) ans.push_back(x);
  ans.push_back(mxe);
  reverse(begin(ans1), end(ans1));
  for (int x: ans1) ans.push_back(x);
  ans.push_back(eg);
  cout << "0";
  for (int x: ans) cout << ' ' << x;
  cout << endl;
  return 0;
}