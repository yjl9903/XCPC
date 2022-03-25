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

int n, m, q, a[maxn];

int main() {
    scanf("%d", &n);
    ll sum = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), sum += a[i];
    sort(a + 1, a + n + 1); reverse(a + 1, a + n + 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &q);
        printf("%I64d\n", sum - a[q]);
    }
    return 0;
}