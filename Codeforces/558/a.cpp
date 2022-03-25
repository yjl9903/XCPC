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

int n, m, vis[maxn];

int main() {
    cin >> n >> m;
    // if (n == m) return puts("0"), 0;
    // if (n == 3 || m == 0) return puts("1"), 0;
    // if (m < n / 2) cout << m;
    // else {
    //     n -= m - n / 2;
    // }
    for (int i = 1; i <= n && m; i += 2, m--) vis[i] = 1;
    for (int i = 1; i <= n && m; i++) {
        if (!vis[i]) {
            vis[i] = 1; m--;
        }
    }
    int ans = 0;
    for (int i = 2, j; i <= n; i = j) {
        if (vis[i]) {
            j = i + 1; continue;
        }
        ans++;
        j = i; while (j <= n && !vis[j]) j++;
    }
    cout << ans;
    return 0;
}