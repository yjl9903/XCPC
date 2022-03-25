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
const int maxn = 300000 + 5;

int n, k, ans[maxn][2];

int main() {
    cin >> n >> k;
    if (n > 1ll * k * (k - 1)) return puts("NO"), 0;
    int tot = 1, f = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = i + 1; j <= k; j++) {
            ans[tot][f] = i;
            ans[tot][f ^ 1] = j;
            tot++; f ^= 1;
            ans[tot][f] = i;
            ans[tot][f ^ 1] = j;
            tot++; f ^= 1;
            if (tot > n) break;
        }
        if (tot > n) break;
    }
    puts("YES");
    for (int i = 1; i <= n; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}