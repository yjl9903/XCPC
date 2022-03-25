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

ll n, k;

int main() {
    cin >> n >> k;
    while (1) {
        if (n == 1) return puts("1"), 0;
        ll tot = 1ll << (n - 1);
        if (k == tot) return printf("%I64d\n", n), 0;
        else if (k < tot) n--;
        else k -= tot, n--;
    }
    return 0;
}