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

int n, m, k;

int main() {
  scanf("%d%d%d", &n, &m, &k);
  if (k > 4 * n * m - 2 * n - 2 * m) {
    puts("NO"); return 0;
  }
  puts("YES");
  vector<pair<int,string> > ans;
  if (n == 1) {
    ans.emplace_back(m - 1, "R");
    ans.emplace_back(m - 1, "L");
  } else if (m == 1) {
    ans.emplace_back(n - 1, "D");
    ans.emplace_back(n - 1, "U");
  } else {
    ans.emplace_back(m - 1, "R");
    ans.emplace_back(m - 1, "DUL");
    ans.emplace_back(1, "D");
    for (int i = 1; i <= n - 2; i++) {
      ans.emplace_back(m - 1, "RDU");
      ans.emplace_back(m - 1, "L");
      ans.emplace_back(1, "D");
    }
    ans.emplace_back(m - 1, "R");
    ans.emplace_back(m - 1, "L");
    ans.emplace_back(n - 1, "U");
  }
  for (int i = 0; i < (int)ans.size(); i++) {
    int sum = ans[i].first * ans[i].second.length();
    if (k >= sum) {
      k -= sum;
    } else {
      if (k == 0) {
        ans.erase(ans.begin() + i, ans.end());
      } else {
        ans.erase(ans.begin() + i + 1, ans.end());
        string last = ans[i].second;
        int len = ans[i].second.length();
        if (k / len) {
          ans[i].first = k / len;
        } else {
          ans.pop_back();
        }
        if (k % len) {
          ans.emplace_back(1, last.substr(0, k % len));
        }
      }
      break;
    }
  }
  if (ans.back().first == 0) ans.pop_back();
  printf("%d\n", ans.size());
  for (auto& x: ans) {
    printf("%d %s\n", x.first, x.second.c_str());
  }
  return 0;
}