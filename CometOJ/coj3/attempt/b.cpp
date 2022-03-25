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

int n, a[maxn], b[maxn], vis[maxn][2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int l1 = -1, r1 = -1, cnt1 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        if (l1 == -1) l1 = i;
        r1 = i;
        cnt1++;
    }
    int l2 = -1, r2 = -1, cnt2 = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) continue;
        if (l2 == -1) l2 = i;
        r2 = i;
        cnt2++;
    }
    if (l1 == -1) {
        cout << r2 - l2 + 1 - cnt2 << endl; return 0;
    }
    if (l2 == -1) {
        cout << r1 - l1 + 1 - cnt1 << endl; return 0;
    }
    int ans = 0;
    if (l2 >= r1) ans = r2 - l1 + 2 - cnt1 - cnt2;
    else if (l1 >= r2) ans = r1 - l2 + 2 - cnt1 - cnt2;
    else if (l2 >= l1 && r2 <= r1) {
        ans = r1 - l1 + 1;
        
    } else if (l1 >= l2 && r1 <= r2) {
        ans = r2 - l2 + 1;
        
    } else {
        int l = min(l1, l2), r = max(r1, r2);
        ans = r - l + 2;
        if (l2 <= r1) {
            for (int i = l2; i < r1; i++) if (b[i] == 1) ans++;
            ans -= cnt1 + cnt2;
        } else {
            for (int i = l1; i < r2; i++) if (a[i] == 1) ans++;
            ans -= cnt1 + cnt2;
        }
    }
    cout << ans << endl;
    return 0;
}