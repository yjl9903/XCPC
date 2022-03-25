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

int n, m, k, h[200];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) scanf("%d", h + i);
        int flag = 1, sum = m;
        for (int i = 1; i < n; i++) {
            if (h[i] + k >= h[i + 1]) {
                int x = max(0, h[i + 1] - k);
                sum += h[i] - x;
                // sum += h[i] + k - h[i + 1];
            } else {
                sum -= h[i + 1] - h[i] - k;
                if (sum < 0) {
                    flag = 0; break;
                }
            }
        }
        if (flag) puts("YES");
        else puts("NO");
    }
    return 0;
}