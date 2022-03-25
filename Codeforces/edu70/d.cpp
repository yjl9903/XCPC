#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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

int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        string ans;
        for (int i = 1; 1ll * i * i <= n; i++) {
            if (n % i) continue;
            if (i + n / i + 2 <= (int)1e5) {
                ans.clear();
                for (int j = 0; j < i; j++) ans += "1";
                ans += "33";
                for (int j = 0; j < n / i; j++) ans += "7";
                break;
            }
        }
        if (!ans.empty()) {
            printf("%s\n", ans.c_str()); continue;
        }
        for (int i = 1; i < n; i++) {
            int x = n - i;
            for (int j = i * 6; 1ll * j * j <= x; j++) {
                if (x % j) continue;
                int sum = 5 + j - 5 * i + x / j;
                if (sum <= (int)1e5) {
                    ans.clear();
                    int a = x / j, b = j - 6 * i, c = 1, d = i;
                    // dbg(a, b, c, d);
                    for (int i = 0; i < a; i++) ans += "1";
                    ans += "33";
                    for (int i = 0; i < b; i++) ans += "7";
                    for (int i = 0; i < c; i++) ans += "1";
                    ans += "33";
                    for (int i = 0; i < d; i++) ans += "7";
                    break;
                }
            }
            if (!ans.empty()) break;
        }
        assert(!ans.empty() && (int)ans.length() <= (int)1e5);
        printf("%s\n", ans.c_str());
    }
    return 0;
}