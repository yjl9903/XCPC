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
const int maxn = 1 << 21;
const double eps = 1e-6;

int n;
double a[maxn];

int main() {
    scanf("%d", &n);
    int ss = 1 << n, ok = 0;
    for (int i = 0; i < ss; i++) {
        scanf("%lf", a + i);
        if (a[i] > eps) {
            ok |= i;
        }
    }
    if (ok != ss - 1) return puts("INF"), 0;
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < ss; s++) {
            if (s >> i & 1) a[s] += a[s ^ (1 << i)];
        }
    }
    double ans = 0;
    for (int s = 0; s < ss; s++) {
        double p = 1.0 - a[ss - 1 - s];
        if (p > eps) p = 1.0 / p;
        else p = 0;
        if (__builtin_popcount(s) % 2) ans += p;
        else ans -= p;
    }
    printf("%.6lf\n", ans);
    return 0;
}