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
const int maxn = 1000 + 5;

int n, m, mp[maxn][maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char s[3]; scanf("%s", s);
            if (s[0] == 'R') mp[i][j] = 1;
        }
    }
    int ans = 0;
    vector<int> h(m + 1, 0), l(m + 1, 1), r(m + 1, m);
    for (int i = 1; i <= n; i++) {
        int lo = 0, ri = m + 1;
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) h[j] = 0, l[j] = 1, lo = j;
            else h[j]++, l[j] = max(l[j], lo + 1);
        }
        for (int j = m; j >= 1; j--) {
            if (mp[i][j]) r[j] = m, ri = j;
            else {
                r[j] = min(r[j], ri - 1);
                ans = max(ans, h[j] * (r[j] - l[j] + 1));
            }
        }
    }
    cout << ans * 3;
    return 0;
}