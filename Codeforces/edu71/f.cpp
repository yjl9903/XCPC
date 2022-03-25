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
const int maxn = 500000 + 5;
const int sz = 800;

int q, block[sz + 5][sz + 5], a[maxn];

int main() {
    scanf("%d", &q);
    int op, x, y;
    while (q--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            for (int i = 1; i <= sz; i++) block[i][x % i] += y;
            a[x] += y;
        } else {
            if (x <= sz) printf("%d\n", block[x][y]);
            else {
                int ans = 0;
                for (int i = y; i < maxn; i += x) ans += a[i];
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}