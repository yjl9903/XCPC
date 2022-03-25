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
typedef pair<double,double> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, d;
PII a[maxn];

int main() {
    cin >> n >> d;
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].first);
    for (int i = 1; i <= n; i++) scanf("%lf", &a[i].second);
    sort(a + 1, a + 1 + n, [](PII a, PII b) {
        double x = double(a.second) / double(a.first);
        double y = double(b.second) / double(b.first);
        return x > y;
    });
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d >= a[i].first) {
            ans += a[i].second; d -= a[i].first;
        } else {
            ans += double(a[i].second) / double(a[i].first) * d;
            break;
        }
    }
    printf("%.2lf", ans);
    return 0;
}