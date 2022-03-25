#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int R, d, n, x[maxn], y[maxn], r[maxn];

double dis(double x, double y) {
    return sqrt(x * x + y * y);
}

int main() {
    scanf("%d%d%d", &R, &d, &n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", x + i, y + i, r + i);
        double a = dis(x[i], y[i]) - 1.0 * r[i];
        double b = dis(x[i], y[i]) + 1.0 * r[i];
        if (a >= (double)(R - d) && b <= (double)R) ans++; 
    }
    cout << ans << endl;
    return 0;
}