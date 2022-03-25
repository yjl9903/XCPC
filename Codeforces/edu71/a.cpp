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

int b, p, f, h, c;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d", &b, &p, &f, &h, &c);
        int ans = 0;
        if (h >= c) {
            int mn = min(b / 2, p);
            ans += mn * h;
            b -= mn * 2;
            mn = min(b / 2, f);
            ans += mn * c;
        } else {
            int mn = min(b / 2, f);
            ans += mn * c; 
            b -= mn * 2;
            mn = min(b / 2, p);
            ans += mn * h;
        }
        printf("%d\n", ans);
    }
    return 0;
}