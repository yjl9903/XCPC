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
const int maxn = 100000 + 5;

int n, m, c, b[maxn];

int main() {
    cin >> n >> m >> c;
    for (int i = 1; i <= m; i++) scanf("%d", b + i);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int tot = c, x;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &x);
            tot += x * b[i];
        }
        if (tot > 0) ans++;
    }
    cout << ans << endl;
    return 0;
}