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
const int maxn = 400000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    map<int,int> mp, mp2;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      mp[a[i]]++;
    }
    int sum = 0;
    for (auto it = mp.rbegin(); it != mp.rend(); it++) {
      if (sum + it->second > n / 2) break;
      sum += it->second;
      mp2[it->first] = it->second;
    }
    if ((int)mp2.size() < 3) {
      puts("0 0 0"); continue;
    }
    int g = mp2.rbegin()->second;
    int s = -1, b = -1;
    int pre = 0;
    for (auto& x: mp2) {
      pre += x.second;
      if (g < pre && g < sum - pre - g) {
        s = sum - pre - g;
        b = pre;
      }
    }
    if (s == -1 && b == -1) puts("0 0 0 ");
    else printf("%d %d %d\n", g, s, b);
  }
  return 0;
}