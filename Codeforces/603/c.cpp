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

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<int> v;
    for(int l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      v.push_back(n / l);
    }
    v.push_back(0);
    reverse(begin(v), end(v));
    printf("%d\n", (int)v.size());
    for (int x: v) printf("%d ", x);
    puts("");
  }
  return 0;
}