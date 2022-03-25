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

int n, m;
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &m, s);
  int p = n;
  vector<int> ans;
  while (p) {
    int len = p <= m ? p : m;
    for (; len > 0; len--) {
      if (s[p - len] == '0') break;
    }
    if (len == 0) return puts("-1"), 0;
    ans.push_back(len);
    p -= len;
  }
  reverse(begin(ans), end(ans));
  for (int x: ans) printf("%d ", x);
  return 0;
}