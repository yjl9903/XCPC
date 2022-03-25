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

int n, s[maxn], l[maxn], v[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        n++;
        for (int i = 1; i <= n; i++) scanf("%d", l + i);
        for (int i = 1; i <= n; i++) scanf("%d", s + i);
        for (int i = 1; i <= n; i++) scanf("%d", v + i);
        double ans = (double)s[1] / v[1];
        ll pre = 0;
        for (int i = 2; i <= n; i++) {
            pre += l[i];
            ans = max(ans, (double)(pre + s[i]) / v[i]);
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}