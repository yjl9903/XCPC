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
string s[maxn];

int main() {
  ios::sync_with_stdio(false);
  int T; cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (s[i] == s[j]) {
          auto check = [&](string x) {
            for (int k = 1; k <= n; k++) {
              if (k == j) continue;
              if (x == s[k]) return false;
            }
            return true;
          };
          int f = 1;
          for (int k = 0; f && k < 4; k++) {
            for (int p = 0; p < 10; p++) {
              if (s[j][k] == p + '0') continue;
              string tot(s[j]);
              s[j][k] = p + '0';
              if (check(tot)) {
                sum++; s[j] = tot;
                f = 0;
                break;
              }
            }
          }
        }
      }
    }
    cout << sum << '\n';
    for (int i = 1; i <= n; i++) {
      cout << s[i] << '\n';
    }
  }
  return 0;
}