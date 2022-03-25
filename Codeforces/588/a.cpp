#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, b[maxn];
ll a[maxn];

int main() {
    scanf("%d", &n);
    map<ll,int> cnt;
    map<ll,ll> mp;
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", a + i);
        cnt[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", b + i);
        mp[a[i]] += b[i];
    }
    vector<ll> key;
    ll ans = 0;
    for (auto& x: cnt) if (x.second >= 2) key.push_back(x.first);
    for (auto& x: mp) {
        for (auto& y: key) {
            if ((x.first & y) == x.first) {
                ans += x.second; break;
            }
        }
    }
    cout << ans;
    return 0;
}