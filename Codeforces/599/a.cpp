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
const int maxn = 100000 + 5;

ll n;

int main() {
  cin >> n;
  vector<ll> p;
  for (int i = 2; 1ll * i * i <= n; i++) {
    if (n % i) continue;
    p.push_back(i);
    while (n % i == 0) n /= i;
  }
  if (n > 1) p.push_back(n);
  if ((int)p.size() == 1) cout << *p.begin();
  else cout << 1;
  return 0;
}