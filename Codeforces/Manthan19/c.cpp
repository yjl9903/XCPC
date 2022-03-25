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
const int maxn = 2000 + 5;

int n, a[maxn][maxn];

int main() {
    cin >> n;
    int tot = 0;
    for (int i = 1; i <= n; i += 2) {
        for (int j = 1; j <= n; j += 2) {
            a[i][j] = tot;
            a[i][j + 1] = tot + 1;
            a[i + 1][j] = tot + 2;
            a[i + 1][j + 1] = tot + 3;
            tot += 4;
        }
    }
    for (int i = 1; i <= n; i++) {
        int sum1 = 0, sum2 = 0;
        for (int j = 1; j <= n; j++) {
            sum1 ^= a[i][j];
            sum2 ^= a[j][i];
        }
        dbg(i, sum1, sum2);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", a[i][j]);
        }
        puts("");
    }
    return 0;
}