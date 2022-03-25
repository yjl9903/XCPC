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
  string a, b;
  cin >> a >> b;
  bool flag = true;
  if (a == "elephant") {
    if (b == "mouse") flag = false;
  } else if (a == "tiger") {
    if (b == "elephant") flag = false;
  } else if (a == "cat") {
    if (b == "tiger") flag = false;
  } else if (a == "mouse") {
    if (b == "cat") flag = false;
  }
  if (flag) puts("tiangou yiwusuoyou");
  else puts("tiangou txdy");
  return 0;
}