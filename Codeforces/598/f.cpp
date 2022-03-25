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
const int maxn = 200000 + 5;

int n;
char s[maxn], t[maxn];

int get(char* s) {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (s[j] > s[i]) ans++;
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%s", &n, s + 1, t + 1);
    vector<int> cnt1(26), cnt2(26);
    for (int i = 1; i <= n; i++) cnt1[s[i] - 'a']++;
    for (int i = 1; i <= n; i++) cnt2[t[i] - 'a']++;
    int flag = -1;
    for (int i = 0; i < 26; i++) if (cnt1[i] != cnt2[i]) flag = 0;
    if (flag == 0) {
      puts("NO"); continue;
    }
    for (int i = 0; i < 26; i++) if (cnt1[i] >= 2) flag = 1;
    for (int i = 0; i < 26; i++) if (cnt2[i] >= 2) flag = 1;
    if (flag == 1) {
      puts("YES"); continue;
    }
    if (get(s) % 2 == get(t) % 2) puts("YES");
    else puts("NO");
  }
  return 0;
}