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

int n; string s;

int main() {
  cin >> n >> s;
  if (n % 2) return puts("No"), 0;
  string half = s.substr(0, n / 2);
  if (half + half == s) puts("Yes");
  else puts("No");
  return 0;
}