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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("%I64d\n", (1ll * n * (n + 1) / 2 + mod - 1) % mod);
    }
    return 0;
}