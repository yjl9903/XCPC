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

int n, r, a[maxn];

int main() {
    scanf("%d%d", &n, &r);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = 0;
    for (int last = 0; last < n; ) {
        int pos = -1;
        for (int i = n; i > max(0, last - r + 1); i--) {
            if (!a[i]) continue;
            if (i - r <= last) {
                pos = i; break;
            }
        }
        if (pos == -1) return puts("-1"), 0;
        ans++; last = pos + r - 1;
    }
    cout << ans;
    return 0;
}