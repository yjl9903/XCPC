#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

char a[maxn], b[maxn];
int cnt[2][30], pre[maxn], suf[maxn];

int main() {
    scanf("%s%s", a, b);
    int n = strlen(a), m = strlen(b);
    for (int i = 0; i < n; i++) cnt[0][a[i] - 'a']++;
    for (int i = 0; i < m; i++) cnt[1][b[i] - 'a']++;
    int flag = 1;
    for (int i = 0; i < 26; i++) {
        if (cnt[0][i] && cnt[1][i]) { flag = 0; break; }
    }
    if (flag) return puts("-"), 0;
    int last = 0;
    for (int i = 0; i < m; i++) {
        if (last == n) { pre[i] = -1; continue; }
        int flag = 1;
        while (last < n) {
            if (a[last] == b[i]) {
                flag = 0;
                pre[i] = last; last++;
                break;
            }
            last++;
        }
        if (flag) pre[i] = -1;
    }
    last = n - 1;
    for (int i = m - 1; i >= 0; i--) {
        if (last == -1) { suf[i] = -1; continue; }
        int flag = 1;
        while (last >= 0) {
            if (a[last] == b[i]) {
                flag = 0; suf[i] = last; last--;
                break;
            }
            last--;
        }
        if (flag) suf[i] = -1;
    }
    // for (int i = 0; i < m; i++) printf("%d ", pre[i]); puts("");
    // for (int i = 0; i < m; i++) printf("%d ", suf[i]); puts("");
    int ans = m, l = -1, r = m + 1;
    for (int i = 0; i < m; i++) if (pre[i] != -1) {
        ans = m - i - 1; l = i;
    }
    for (int i = m - 1; i >= 0; i--) if (suf[i] != -1) {
        if (i < ans) ans = i, l = -1, r = i;
    }
    for (int i = 0; i < m; i++) {
        if (pre[i] == -1) break;
        int rk = upper_bound(suf, suf + m, pre[i]) - suf;
        if (rk - i - 1 < ans) l = i, r = rk, ans = rk - i - 1;
    }
    if (ans == m) return puts("-"), 0;
    for (int i = 0; i < m; i++) if (i <= l || i >= r) putchar(b[i]); 
    // cout << l << ' ' << r << endl;
    return 0;
}