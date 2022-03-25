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
  ios::sync_with_stdio(false);
  string a, b;
  cin >> a >> b;
  int len = 0;
  while (len < a.length() && 'a' <= a[len] && a[len] <= 'z') len++;
  string c = a.substr(0, len);
  string d = b.substr(0, len);
  string x = a.substr(len);
  string y = b.substr(len);
  // ll x = atol(a.substr(len).c_str());
  // ll y = atol(b.substr(len).c_str());
  // cout << c << endl;
  // cout << d << endl;
  // cout << x << endl;
  // cout << y << endl;
  if (c != d) {
    puts(c < d ? "<" : ">");
  } else {
    if (x.length() != y.length()) {
      puts(x.length() < y.length() ? "<" : ">");
    } else if (x != y) {
      puts(x < y ? "<" : ">");
    } else {
      puts("=");
    }
  }
  return 0;
}