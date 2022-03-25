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
const int maxn = 300000 + 5;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int n, m;
ll x[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%I64d", x + i);
    ll g = x[2] - x[1];
    for (int i = 3; i <= n; i++) {
        g = gcd(g, x[i] - x[i - 1]);
    }
    for (int i = 1; i <= m; i++) {
        ll p; scanf("%I64d", &p);
        if (g % p == 0) {
            puts("YES");
            printf("%I64d %d", x[1], i);
            return 0;
        }
    }
    puts("NO");
    return 0;
}