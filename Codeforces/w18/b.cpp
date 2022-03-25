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
const int maxn = 3000 + 5;

int n, s[maxn], c[maxn], f[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", s + i);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    ms(f, -1);
    for (int i = n - 1; i >= 1; i--) {
        int k = 1e9;
        for (int j = i + 1; j <= n; j++) {
            if (s[j] > s[i]) k = min(k, c[j]);
        }
        if (k != (int)1e9) f[i] = c[i] + k;
    }
    // for (int i = 1; i <= n; i++) cout << f[i] << ' '; cout << endl;
    int ans = (int)1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j + 1 <= n; j++) {
            if (f[j] == -1) continue;
            if (s[j] > s[i]) ans = min(ans, c[i] + f[j]); 
        }
    }
    if (ans == (int)1e9) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}