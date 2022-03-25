#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
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
const int maxn = 1000000 + 5;

int f[20][20], k, x;

ll res[maxn];
unordered_map<ll,int> mp;
void dfs(int now, int val, int sum) {
    if (now == 0) {
        res[val] = sum;
        mp[sum - val * 100000ll]++;
        return ;
    }
    // if (now == 1) {
    //     mp[sum - val * 100000]++;
    // }
    for (int i = 0; i <= 9; i++) {
        dfs(now - 1, val * 10 + i, sum + f[i][k]);
    }
}

int main() {
    for (int i = 1; i <= 10; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= 9; j++) f[i][j] = i * f[i][j - 1];
    }
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        mp.clear();
        scanf("%d%d", &x, &k);
        dfs(5, 0, 0);
        int ans = 0;
        for (int i = 1; i < (int)1e5; i++) {
            if (mp.count(x - res[i] + i)) {
                ans += mp[x - res[i] + i];
                dbg(i, res[i], mp[x - res[i] + i]);
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}