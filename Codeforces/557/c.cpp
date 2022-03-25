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

int n, k, a[maxn], l[maxn], r[maxn];

int main() {
    scanf("%d%d", &n, &k);
    if (n == 1) return puts("0"), 0;
    for (int i = 1; i <= k; i++) {
        scanf("%d", a + i);
        if (l[a[i]] == 0) l[a[i]] = i;
        r[a[i]] = i;
    }
    int ans = 0;

    if (l[1] == 0) ans += 2;
    else if (l[1] > r[2]) ans++;
    if (l[n] == 0) ans += 2;
    else if (l[n] > r[n - 1]) ans++;
    
    for (int i = 2; i < n; i++) {
        if (l[i] == 0) {
            ans += 3;
        } else {
            if (l[i] > r[i - 1]) ans++;
            if (l[i] > r[i + 1]) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}