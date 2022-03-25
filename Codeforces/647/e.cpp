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

int n, k;

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> k;
  if (n % (k + 1) == 0) {
    cout << "X" << endl;
  } else {
    cout << "E " << n % (k + 1) << endl;
    n -= n % (k + 1);
    while (n > 0) {
      int x;
      cin >> x;
      cout << "E " << k + 1 - x << endl;
      n -= k + 1;
    }
  }
  return 0;
}