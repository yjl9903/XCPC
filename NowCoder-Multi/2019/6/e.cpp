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

int n, G[maxn][maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("Case #%d: ", ++kase);
        if (n % 4 == 2 || n % 4 == 3) {
            puts("No"); continue;
        }
        puts("Yes");
        if (n == 1) {
            puts("0\n1"); continue;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) G[i][j] = 0;
        for (int t = 1; t <= n / 2; t += n / 4) {
            for (int i = t; i < t + n / 4; i++) {
                for (int j = i + 1; j < t + n / 4; j++) {
                    G[i][j] = G[j][i] = 1;
                }
            }
        }
        for (int i = 1; i <= n / 4; i++) {
            for (int j = n / 4 + 1; j <= n / 2; j++) {
                G[i][j] = G[j][i] = 1;
            }
            for (int j = n / 2 + 1; j <= n / 4 + n / 2; j++) {
                G[i][j] = G[j][i] = 1;
            }
        }
        for (int i = n / 4 + 1; i <= n / 2; i++) {
            for (int j = n / 4 + n / 2 + 1; j <= n / 4 * 4; j++) {
                G[i][j] = G[j][i] = 1;
            }
        }
        if (n % 4 == 1) {
            for (int i = 1; i <= n / 2; i++) G[i][n] = G[n][i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) putchar(G[i][j] + '0');
            puts("");
        }
        vector<int> ans;
        for (int i = 1; i <= n / 4; i++) ans.push_back(n / 2 + i);
        for (int i = n / 4 + 1; i <= n / 2; i++) ans.push_back(n / 2 + i);
        for (int i = n / 2 + 1; i <= n / 4 + n / 2; i++) ans.push_back(i - n / 4);
        for (int i = n / 4 + n / 2 + 1; i <= n / 4 * 4; i++) ans.push_back(i - n / 4 - n / 2);
        if (n % 4) ans.push_back(n);
        for (int i = 0; i < n; i++) {
            if (i) putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}