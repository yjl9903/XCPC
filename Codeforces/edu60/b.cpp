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
const int maxn = 300000 + 5;

int n, m, k, a[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    int t = m / (k + 1), r = m % (k + 1);
    // cout << t << ' ' << r << endl;
    cout << 1ll * t * (1ll * k * a[n - 1] + a[n - 2]) + 1ll * r * a[n - 1] << endl;
    return 0;
}