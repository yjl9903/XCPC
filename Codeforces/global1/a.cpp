#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 2;
const int maxn = 100000 + 5;

int qpow(int x, int n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int b, k;

int main() {
    scanf("%d%d", &b, &k);
    int ans = 0;
    while (k--) {
        int x; scanf("%d", &x);
        ans += x * qpow(b, k) % mod;
    }
    if (ans % 2) puts("odd");
    else puts("even");
    return 0;
}