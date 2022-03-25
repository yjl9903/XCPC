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

int n, a, b;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        cin >> n >> a >> b;
        int g = __gcd(a, b);
        int c = n / g;
        printf("Case #%d: ", ++kase);
        if (c % 2 == 0) puts("Iaka");
        else puts("Yuwgna");
    }
    return 0;
}