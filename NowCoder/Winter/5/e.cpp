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
const int maxn = 100000 + 5;

int main() {
  ll n; cin >> n;
  if (n % 2 == 1) {
    puts("Bob");
  } else if (__builtin_popcountll(n) == 1) {
    puts("Alice");
  } else {
    puts("Bob");
  }
  return 0;
}