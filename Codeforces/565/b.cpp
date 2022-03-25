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

int n, a[maxn], cnt[3];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        cnt[0] = cnt[1] = cnt[2] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i); cnt[a[i] % 3]++;
        }
        int ans = cnt[0] + min(cnt[1], cnt[2]);
        int x = min(cnt[1], cnt[2]);
        cnt[1] -= x; cnt[2] -= x;
        printf("%d\n", ans + cnt[1] / 3 + cnt[2] / 3);
    }
    return 0;
}