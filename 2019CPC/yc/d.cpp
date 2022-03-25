#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

int n, m;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        printf("Case #%d: ", ++kase);
        if (n == 1) printf("%.6lf ", 1.0);
        else printf("%.6lf ", 0.5);
        if (m == 1) printf("%.6lf\n", 1.0);
        else printf("%.6lf\n", 1.0 * (m + 1) / (2.0 * m));
    }
    return 0;
}