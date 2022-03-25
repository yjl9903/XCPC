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

int a[50];

int main() {
    ll x;
    while (scanf("%lld", &x) == 1) {
        int tot = 0;
        while (x) {
            a[tot] = (a[tot] + x % 3) % 3;
            tot++; x /= 3;
        }
    }
    ll ans = 0, b = 1;
    for (int i = 0; i < 30; i++) {
        ans += b * a[i];
        b *= 3ll;
    }
    cout << ans << endl;
    return 0;
}