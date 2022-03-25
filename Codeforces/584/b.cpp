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

int n, a[maxn], b[maxn];
char s[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
    int ans = 0;
    for (int t = 0; t < maxn; t++) {
        int c = 0;
        for (int i = 1; i <= n; i++) {
            if (t < b[i]) {
                c += s[i] - '0';
            } else {
                int tot = ((t - b[i]) / a[i]) % 2;
                if (s[i] == tot + '0') {
                    c++;
                }
            }
        }
        ans = max(ans, c);
    }
    cout << ans;
    return 0;
}