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

int r, g, b;

int main() {
  ios::sync_with_stdio(false);
  int T; cin >> T;
  while (T--) {
    cin >> r >> g >> b;
    int mx = max(r, max(g, b));
    int sum = r + g + b;
    if (mx + mx <= sum) printf("%d\n", sum / 2);
    else {
      // vector<int> v = {r, g, b};
      // sort(begin(v), end(v));
      printf("%d\n", sum - mx);
    }
  }
  return 0;
}