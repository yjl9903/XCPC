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

int n, v;

int main() {
    cin >> n >> v;
    if (v >= n - 1) return printf("%d", n - 1), 0;
    int tot = v, ans = v;
    for (int i = 2; i <= n; i++) {
        tot--;
        if (tot < n - i) {
            int nd = min(n - i - tot, v - tot);
            tot += nd; ans += i * nd;
        }
    }
    cout << ans << endl;
    return 0;
}