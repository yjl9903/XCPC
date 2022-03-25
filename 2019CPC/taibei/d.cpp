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



int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  vector<string> ans;
  string s;
  while (cin >> s) {
    if (s != "bubble" && s != "tapioka") {
      ans.push_back(s);
    }
  }
  if (ans.empty()) {
    cout << "nothing" << endl;
  } else {
    for (auto& x: ans) cout << x << ' ';
    cout << endl;
  }
  return 0;
}