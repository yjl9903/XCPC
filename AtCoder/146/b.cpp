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
string s;

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> s;
  string ans;
  for (auto& x: s) {
    char tot = (x - 'A' + n) % 26 + 'A';
    ans.push_back(tot);
  }
  cout << ans;
  return 0;
}