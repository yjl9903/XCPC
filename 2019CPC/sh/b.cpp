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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, q;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        vector<PII> que;
        for (int i = 1, l, r; i <= q; i++) {
            scanf("%d%d", &l, &r); l++; r++;
            que.push_back({l, 1});
            que.push_back({r + 1, -1});
        }
        sort(que.begin(), que.end());
        int ans = 0, tot = 0, m = (int)que.size();
        for (int i = 0, j; i < m; i = j) {
            j = i;
            while (j < m && que[j].first == que[i].first) {
                tot += que[j].second; j++;
            }
            if (tot % 2 && j < m) {
                int nex = que[j].first;
                ans += nex - que[i].first;
            }
            // dbg(que[i].first);
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}