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

ll l, r, x, y, k;

int main() {
    cin >> l >> r >> x >> y >> k;
    for (ll i = x; i <= y; i++) {
        if (k * i >= l && k * i <= r) return puts("YES"), 0;
    }
    puts("NO");
    return 0;
}