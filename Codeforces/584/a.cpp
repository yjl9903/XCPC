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

int n, a[maxn], vis[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1; ans++;
        for (int j = i + 1; j <= n; j++) {
            if (a[j] % a[i] == 0) {
                vis[j] = 1;
            }
        }
    }
    cout << ans;
    return 0;
}