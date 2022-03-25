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
const int maxn = 100000 + 5;

ll n, a, b;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%I64d%I64d%I64d", &n, &a, &b);
        if (b > 2 * a) b = 2 * a;
        ll ans = 1ll * n / 2 * b + n % 2 * a;
        printf("%I64d\n", ans);
    }
    return 0;
}