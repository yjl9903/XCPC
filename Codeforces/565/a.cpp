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



int main() {
    int T; scanf("%d", &T);
    while (T--) {
        ll x; cin >> x;
        int ans = 0;
        while (x % 2 == 0) {
            ans++; x /= 2;
        }
        while (x % 3 == 0) {
            ans += 2; x /= 3;
        }
        while (x % 5 == 0) {
            ans += 3; x /= 5;
        }
        if (x > 1) puts("-1");
        else printf("%d\n", ans);
    }
    return 0;
}