#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

double a[maxn];

int main() {
  freopen("../input/out.txt", "r", stdin);
  ios::sync_with_stdio(false);
  int n = 50000;
  for (int i = 1; i <= n; i++) cin >> a[i];
  double d1 = inf, d2 = inf;
  for (int i = 3; i <= n; i += 2) {
    d1 = min(d1, a[i] - a[i - 2]);
  }
  for (int i = 4; i <= n; i += 2) {
    d2 = min(d2, a[i - 2] - a[i]);
  }
  cout << d1 << endl << d2 << endl;
  return 0;
}