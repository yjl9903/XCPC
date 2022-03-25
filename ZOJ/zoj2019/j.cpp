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

bool isprime(int x) {
    for (int i = 2; 1ll * i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        // if (n % 2 == 0) printf("%d %d\n", n, n + n);
        // else {
        printf("%lld %lld\n", 8ll * n, 9ll * n);
        // }
    }
    return 0;
}