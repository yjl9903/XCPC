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

int n, a[maxn];

int main() {
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) cin >> a[i];
    sort(a + 1, a + 1 + 2 * n);
    ll sum = 0, sum2 = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    for (int i = n + 1; i <=2 * n; i++) sum2 += a[i];
    if (sum == sum2) puts("-1");
    else {
        for (int i = 1; i <= 2 * n; i++) cout << a[i] << ' ';
    }
    return 0;
}