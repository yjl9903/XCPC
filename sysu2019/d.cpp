#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;

int n, m, p, q;
int a[maxn * 10];

int getid(int i, int j) {
    return i * m + j;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        scanf("%d", &p);
        for (int i = 1; i <= p; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            a[getid(x1, y1)]++;
            a[getid(x1, y2 + 1)]--;
            a[getid(x2 + 1, y1)]--;
            a[getid(x2 + 1, y2 + 1)]++;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            a[getid(i, j)] += -a[getid(i - 1, j - 1)] + a[getid(i - 1, j)] + a[getid(i, j - 1)];
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            if (a[getid(i, j)] > 0) a[getid(i, j)] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            a[getid(i, j)] += -a[getid(i - 1, j - 1)] + a[getid(i - 1, j)] + a[getid(i, j - 1)];
        }
        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= m; j++) {
        //         printf("%d ", a[getid(i, j)]);
        //     }
        //     puts("");
        // }
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int sum = a[getid(x2, y2)] + a[getid(x1 - 1, y1 - 1)] - a[getid(x1 - 1, y2)] - a[getid(x2, y1 - 1)];
            dbg(sum);
            if (sum == (x2 - x1 + 1) * (y2 - y1 + 1)) {
                puts("YES");
            } else {
                puts("NO");
            }
        }
        ms(a, 0);
        // for (int i = 0; i <= (n + 1) * m; i++) a[i] = 0;
    }  
    return 0;
}