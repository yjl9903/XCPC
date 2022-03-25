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
  ll n1, n2, n12;
  cin >> n1 >> n2 >> n12;
  ll ans = (n1 + 1) * (n2 + 1) / (n12 + 1) - 1;
  cout << ans << endl;
  return 0;
}