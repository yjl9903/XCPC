#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m, k, a[maxn], b[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    ll sum = n;
    for (int i = 0; i < n - 1; i++) b[i] = a[i + 1] - a[i] - 1;
    // for (int i = 0; i < n - 1; i++) cout << b[i] << endl;
    sort(b, b + n - 1);
    for (int i = 0; i < n - k; i++) sum += b[i];
    cout << sum << endl;
    return 0;
}