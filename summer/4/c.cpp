#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int x, y, k;

int check(int c) {
    int a = 11 * y * (k - c);
    // int b = (9 * y - 11 * x);
    for (int i = 0; i < c; i++) {
        a += 9 * y - 11 * x;
        if (a < 0) return 0;
    }
    return 1;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &x, &y, &k);
        swap(x, y);
        printf("Case #%d: ", ++kase);
        if (y > x) printf("%d\n", k);
        else {
            int l = 0, r = k, ans = 0;
            while (l <= r) {
                int m = (l + r) / 2;
                if (check(m)) ans = m, l = m + 1;
                else r = m - 1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}