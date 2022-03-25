#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a, b, c, d;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int ans = 5;
        if (a < 0 && c > 0) ans++;
        if (b < 0 && d > 0) ans++;
        if (ans == 7) ans++;
        printf("%d\n", ans);
    }
    return 0;
}