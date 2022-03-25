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

int f[2][2][2][2][2][2];

int main() {
  for (int i = 0; i < 2; i++) {
    f[1][i][0][1][i][0] = 8;
    f[0][i][1][0][i][1] = 8;
    f[0][i][0][0][i][0] = 8;
    f[1][i][1][1][i][1] = 8;

    f[1][i][1][0][i][1] = 6;
    f[1][i][0][0][i][0] = 6;
    f[0][i][1][1][i][1] = 6;
    f[0][i][0][1][i][0] = 6;

    f[1][i][1][1][i][0] = 6;
    f[0][i][1][0][i][0] = 6;
    f[1][i][0][1][i][1] = 6;
    f[0][i][0][0][i][1] = 6;

    f[1][i][1][0][i][0] = 6;
  }
  vector<int> key;
  for (int i = 0; i < 6; i++) {
    string x;
    cin >> x;
    key.push_back(x == "true" ? 1 : 0);
  }

  return 0;
}