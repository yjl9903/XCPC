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

int n, k, alive[maxn];
int query(int x) {
  cout << "? " << x << endl;
  string s; cin >> s;
  if (s == "Y") {
    alive[x] = false;
    return true;
  } else {
    return false;
  }
}
void reset() {
  cout << "R" << endl;
}

int main() {
  cin >> n >> k;
  fill(alive + 1, alive + 1 + n, true);
  int B = max(k / 2, 1), Bcnt = n / B;
  for (int i = 1; i <= Bcnt; i++) {
    for (int j = 0; j < i && i + j < Bcnt; j++) {
      for (int k = j; k < Bcnt; k += i) {
        for (int p = 1; p <= B; p++) {
          query(k * B + p);
        }
      }
      reset();
    }
  }
  cout << "! " << count(alive + 1, alive + 1 + n, true) << endl;
  return 0;
}