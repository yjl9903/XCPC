#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const double eps = 1e-8;

int n, m, x[maxn], d[maxn];

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> x[i] >> d[i];
    double res = 0;
    ll sum = 0;
    ll mm = n / 2;
    ll k = 1ll * n * (n - 1) / 2, k2 = 0;
    for (int i = 0; i < n; i++) k2 += abs(i - mm);
    for (int i = 0; i < m; i++){
        sum += 1ll * n * x[i];
        if (d[i] > 0)  sum += k * 1ll *  d[i];
        else if (d[i] < 0)  sum += k2 * 1ll * d[i];
    }
    res = (double)sum / n;
    printf("%.8f", res);
    return 0;
}