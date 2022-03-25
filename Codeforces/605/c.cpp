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
const int maxn = 200000 + 5;

int n, k;
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  set<char> st;
  for (int i = 0; i < k; i++) {
    char ch[5]; scanf("%s", ch);
    st.insert(ch[0]);
  }
  ll ans = 0; int last = 0;
  for (int i = 1; i <= n + 1; i++) {
    if (i > n || !st.count(s[i])) {
      int len = i - last - 1;
      ans += 1ll * len * (len + 1) / 2;
      last = i;
    }
  }
  printf("%I64d\n", ans);
  return 0;
}