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

int n;
double a[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%lf", a + i);
        }
        double ans = 0.0;
        for (int s = 1; s < (1 << n); s++) {
            int c = 0; double sum = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    c++;
                    sum += a[i];
                }
            }
            if (c % 2) ans += 1.0 / sum;
            else ans -= 1.0 / sum;
        }
        printf("%.4lf\n", ans);
    }
    return 0;
}