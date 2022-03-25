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

int mu[maxn], vis[maxn], prime[maxn], tot;
void getMu() {
    mu[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] < maxn; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

int main() {
  getMu();
  for (int i = 1; i <= 60; i++) {
    cout << mu[i] << endl;
  }
  return 0;
}