#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, r, x[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &r);
        vector<int> lsh;
        for (int i = 1; i <= n; i++) {
            scanf("%d", x + i);
            lsh.push_back(x[i]);
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        int ans = 0, m = (int)lsh.size();
        for (int i = m - 1; i >= 0; i--) {
            ans++;
            if (i && lsh[i - 1] <= 1ll * ans * r) break;
        }
        printf("%d\n", ans);
    }
    return 0;
}