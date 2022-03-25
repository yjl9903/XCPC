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

int n, m, a[maxn], b[maxn];

int main() {
    scanf("%d%d", &n, &m);
    int c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] % 2) c2++;
        else c1++;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", b + i);
        if (b[i] % 2) d2++;
        else d1++;
    }
    cout << min(c1, d2) + min(c2, d1);
    return 0;
}