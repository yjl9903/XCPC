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

string a = "1", b = "14", c = "144";
set<string> all;

void dfs(string tot) {
  if (tot.length() > 10) return ;
  if (all.count(tot)) return ;
  all.insert(tot);
  dfs(tot + a);
  dfs(tot + b);
  dfs(tot + c);
}

int main() {
  dfs(a); dfs(b); dfs(c);
  int T; scanf("%d", &T);
  while (T--) {
    int x; scanf("%d", &x);
    if (all.count(to_string(x))) printf("YES\r\n");
    else printf("NO\r\n");
  }
  return 0;
}