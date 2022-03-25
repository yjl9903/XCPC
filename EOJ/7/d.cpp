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

ll n; int q, a, b, c, d;

int mp[30][30];

int main() {
    scanf("%lld%d", &n, &q);
    for (int i = 1; i <= n; i++) mp[i][i] = mp[n - i + 1][i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mp[i][j] += -mp[i - 1][j - 1] + mp[i - 1][j] + mp[i][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", mp[i][j]);
        }
        puts("");
    }
    while (q--) {

    }
    return 0;
}