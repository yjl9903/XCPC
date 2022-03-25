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
const int maxn = 100 + 5;

int n, m; char s[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
        int mx = 0, p = 0, l = 0, r = 0;
        for (int i = 1; i <= n; i++) {
            int c = 0, tl = -1, tr = -1;
            // cout << s[i] + 1 << endl;
            for (int j = 1; j <= m; j++) {
                if (s[i][j] == '.') {
                    c++;
                    tr = j;
                    if (tl == -1) tl = j;
                }
            }
            if (c > mx) mx = c, p = i, l = tl, r = tr;
        }
        // cout << l << ' ' << r << endl;
        // cout << mx << endl;
        printf("%d %d %d\n", mx / 2, p, (l + r) / 2);
    }
    return 0;
}