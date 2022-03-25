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
const int maxn = 100000 + 5;

int x;

int main() {
    cin >> x;
    ll ans = 1; int cnt = 1;
    while (1) {
        if (ans % x == 0) return printf("%lld %d", ans / x, cnt);
        ans = 10ll * ans + 1; cnt++;
    }
    return 0;
}