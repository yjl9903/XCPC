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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

char s[maxn];

int main() {
  int T;
  cin >> T;
  cin.ignore();
  while (T--) {
    cin.getline(s + 1, 100005);
    int n = strlen(s + 1);
    int last = true;
    for (int i = 1; i <= n; i++) {
      if (s[i] == ':' || s[i] == '-') {
        if (!last) {
          cout << ' ';
        }
        cout << s[i];
        if (i < n && s[i + 1] != ' ') {
          cout << ' ';
          last = true;
        }
      } else if (s[i] == ' ') {
        cout << ' ';
        last = true;
      } else {
        cout << s[i];
        last = false;
      }
    }
    cout << '\n';
  }
  return 0;
}