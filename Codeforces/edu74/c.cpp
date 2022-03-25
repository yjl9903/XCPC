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
const int maxn = 200000 + 5;

int h, n, p[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &h, &n);
        for (int i = 1; i <= n; i++) scanf("%d", p + i);
        int ans = 0; p[n + 1] = 0;
        for (int i = 2; i <= n; i++) {
            if (p[i] - p[i + 1] == 1) {
                i++;
            } else {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}