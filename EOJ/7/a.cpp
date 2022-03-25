#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

int check(ll x) {
    ll sq = sqrt(x);
    return sq * sq == x;
}
int get(int x) {
    for (int i = x - 1; i >= 2; i--) if (check(1ll * i * x)) return i;
    return -1;
}

int main() {
    cin >> n;
    int sq = sqrt(n);
    if (sq * sq == n) return cout << n, 0;
    int ans = -1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) ans = i;
    }
    ans = max(ans, get(n));
    printf("%d\n", ans);
    return 0;
}