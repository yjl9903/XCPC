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

int n, m, k, a[maxn], cnt[2000], tot[2000];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        ms(cnt, 0); ms(tot, 0);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
        int ans = 0;
        for (int i = 1; i <= n / 2; i++) {
            tot[a[i]]++;
            if (tot[a[i]] <= cnt[a[i]] / k) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}