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
  cin >> n;
  int l = 1, r = n, ans = 0;
  char s[10];
  while (l <= r) {
    int m = (l + r) / 2;
    cout << "? " << m << endl;
    cin >> s;
    if (s[0] == '<') {
      r = m - 1;
    } else if (s[0] == '>') {
      ans = m; l = m + 1;
    }
  }
  cout << "! " << ans << endl; 
  return 0;
}