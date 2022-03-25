#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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

int n, m, a[5][300];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        vector<vector<int> > mp;
        for (int i = 1; i <= m; i++) {
            vector<int> v;
            for (int j = 1; j <= n; j++) {
                v.push_back(a[j][i]);
            }
            sort(v.begin(), v.end());
            reverse(v.begin(), v.end());
            v.push_back(i);
            mp.push_back(v);
        }
        sort(mp.begin(), mp.end());
        reverse(mp.begin(), mp.end());
        mp.resize(min(n, m));
        int ans = 0;
        for (int i = 0; i < min(n, m); i++) {
            dbg(mp[i][n]);
            ans += mp[i][0];
        }
        printf("%d\n", ans);
    }
    return 0;
}