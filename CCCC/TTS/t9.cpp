#include <bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 5;

int n, m, smax, used[maxn];
char s[maxn][maxn];

int main() {
  scanf("%d%d%d", &n, &m, &smax);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
  }
  string stk;
  string ans;
  while (true) {
    int op;
    scanf("%d", &op);
    if (op == -1) break;
    if (op == 0) {
      if (!stk.empty()) {
        ans += stk.back();
        stk.pop_back();
      }
    } else {
      used[op]++;
      char ch = s[op][used[op]];
      if (ch >= 'A' && ch <= 'Z') {
        if (stk.size() == smax) {
          ans += stk.back();
          stk.pop_back();
        }
        stk.push_back(ch);
      }
    }
  }
  puts(ans.c_str());
  return 0;
}