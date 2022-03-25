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

ll a, b, c;

int main() {
    cin >> a >> b >> c;
    ll ans = 2 * c;
    if (a < b) {
        ans += a + a + 1;
    } else if (a == b) {
        ans += a + b;
    } else {
        ans += b + b + 1;
    }
    cout << ans;
    return 0;
}