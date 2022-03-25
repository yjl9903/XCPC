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
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &a, &b, &n);
        // 0 -> a, 1 -> b, 2 -> a ^ b, 3 -> a, 4 -> b
        if (n % 3 == 0) printf("%d\n", a);
        else if (n % 3 == 1) printf("%d\n", b);
        else printf("%d\n", a ^ b);
    }
    return 0;
}