#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m, cn[maxn], cm[maxn];
set<PII> mp;
char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        mp.clear();
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) cn[i] = 0;
        for (int i = 1; i <= m; i++) cm[i] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++) {
                if (s[j] == '*') cn[i]++, cm[j]++, mp.insert({i, j});
            }
        }
        int ans = maxn;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            ans = min(ans, n + m - 1 - (cn[i] + cm[j] - (int)mp.count({i, j})));
        }
        printf("%d\n", ans);
    }
    return 0;
}