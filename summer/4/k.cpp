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



int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        unsigned long long n; cin >> n;
        printf("Case #%d: ", ++kase);
        if (n == 0) puts("1");
        else if (n == 1) puts("9");
        else if (n == 2) puts("41");
        else if (n == 3) puts("109");
        else { 
            unsigned long long ans = 1 + 14ull * n * n - 6 * n + 4;
            printf("%llu\n", ans);
        }
    }
    return 0;
}