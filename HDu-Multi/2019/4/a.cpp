#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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

int n;

int get(int x) {
    int c = 1;
    while (x) {
        if (x % 2 == 1) x /= 2;
        else {
            break;
        }
        c <<= 1;
    }
    return c;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> fa;
        int ans = 0;
        for (int i = 2; i <= n; i++) {
            // dbg(i, get(i));
            int x = get(i);
            if (x <= n) fa.push_back(x);
            else fa.push_back(1), ans += 1 & i;
        }
        printf("%d\n", ans);
        for (int i = 0; i < n - 1; i++) {
            if (i) putchar(' ');
            printf("%d", fa[i]);
        }
        puts("");
    }
    return 0;
}