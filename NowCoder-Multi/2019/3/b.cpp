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
const int maxn = 100000 + 5;

int n, cnt[maxn][3];
char s[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    map<int,int> mp1, mp2;
    mp1[0] = 0; mp2[0] = 0;
    for (int i = 1; i <= n; i++) {
        cnt[i][0] = cnt[i - 1][0];
        cnt[i][1] = cnt[i - 1][1];
        cnt[i][s[i] - '0']++;
        // mp[cnt[i][0] - cnt[i][1]]++;
        if (!mp1.count(cnt[i][0] - cnt[i][1])) {
            mp1[cnt[i][0] - cnt[i][1]] = i;
        }
        mp2[cnt[i][0] - cnt[i][1]] = i;
        dbg(cnt[i][0] - cnt[i][1], i);
    }
    int ans2 = min(cnt[n][0], cnt[n][1]) * 2;
    int ans1 = 0;
    for (auto& x: mp1) {
        dbg(x.first, x.second);
        if (mp2.count(x.first)) {
            ans1 = max(ans1, mp2[x.first] - x.second);
        }
    }
    cout << ans1 << ' ' << ans2;
    return 0;
}