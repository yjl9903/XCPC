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
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

mt19937 rnd(time(nullptr));

int n, m, cnt[maxn], a[maxn];

int guess(int x) {
  cout << x << endl;
  cin >> x;
  return x;
}

int main() {
  cin >> n >> m;
  int pos = rnd() % n;
  int sum = 0;
  for (int i = 1; i <= m; i++) {
    string pred;
    cin >> pred;
    int pos = rnd() % n, val = rnd() % 2;
    bool flag = false;
    if (sum > 100 && rnd() % 5 <= 3) {
      flag = true;
      int cur = rnd() % (sum - 100);
      for (int i = 0; i < n; i++) a[i] = cnt[i];
      sort(a, a + n, greater<int>());
      for (int i = 0; i < n; i++) {
        if (cur <= a[i]) {
          pos = i;
        } else {
          cur -= a[i];
        }
      }
    }
    int r = guess(flag ? pred[pos] - '0' : val);
    for (int i = 0; i < n; i++) {
      if (r + '0' == pred[i]) {
        cnt[i]++;
        sum++;
      }
    }
  }
  return 0;
}