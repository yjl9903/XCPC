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

int n, k;

map<int,int> sg;
int dfs(int u) {
    if (sg.count(u)) return sg[u];
    if (u < k) return u % 3 != 0;
    int f1 = dfs(u - 1), f2 = dfs(u - 2), f3 = dfs(u - k);
    if (!f1 || !f2 || !f3) return sg[u] = 1;
    return sg[u] = 0;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        if (k > n) {
            if (n % 3 == 0) puts("Bob");
            else puts("Alice");
        } else if (k == n) {
            puts("Alice");
        } else {
            sg.clear();
            sg[0] = 0; sg[1] = 1; sg[2] = 1; sg[k] = 1;
            // if (dfs(n)) puts("Alice");
            // else puts("Bob");
            for (int i = 0; i <= n; i++) {
                dbg(i, dfs(i));
            }
        }
    }
    return 0;
}