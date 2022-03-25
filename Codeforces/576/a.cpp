#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int maxn = 500000 + 5;

int n, I, a[maxn];

int main() {
    scanf("%d%d", &n, &I);
    int up = 8 * I / n;
    if (up >= 22) return puts("0"), 0;
    int mx = 1 << up;
    map<int,int> mp;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mp[a[i]]++;
    int sz = (int)mp.size();
    vector<int> v, suf(sz + 1);
    for (auto& x: mp) v.push_back(x.second);
    for (int i = sz - 1; i >= 0; i--) suf[i] = suf[i + 1] + v[i];
    int ans = inf, pre = 0;
    for (int i = 0; i < sz; i++) {
        int pos = min(sz - 1, i + mx - 1);
        ans = min(ans, pre + suf[pos + 1]);
        pre += v[i];
    }
    cout << ans;
    return 0;
}