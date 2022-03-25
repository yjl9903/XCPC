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

int n, x, y, d;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> n >> x >> y >> d;
        if (abs(x - y) % d) {
            int ans = 2e9;
            if ((y - 1) % d == 0) {
                ans = (y - 1) / d + (x - 1) / d;
                if ((x - 1) % d) ans++;
            } 
            if ((n - y) % d == 0) {
                int tot = (n - y) / d + (n - x) / d;
                if ((n - x) % d) tot++;
                ans = min(ans, tot);
            }
            if (ans == 2e9) puts("-1");
            else printf("%d\n", ans);
        } else {
            printf("%d\n", abs(x - y) / d);
        }
    }
    return 0;
}