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
const int maxn = 300000 + 5;

int n, a[maxn], b[maxn], cnt[maxn];

int solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
    for (int i = 1; i <= n; i++) scanf("%d", b + i), cnt[b[i]]--;
    // for (int i = 0; i < maxn; i++) if (cnt[i]) return puts("NO"), 0;
    int f = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[a[i]]) f = 1;
        cnt[a[i]] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[b[i]]) f = 1;
        cnt[b[i]] = 0;
    }
    if (f) return puts("NO"), 0;
    int st = 1; b[n + 1] = -1;
    for (int i = 1; i <= n; i++) {
        if (b[i] > b[i + 1]) {
            sort(a + st, a + i + 1); st = i + 1;
        }
    }
    for (int i = 1; i <= n; i++) if (a[i] != b[i]) return puts("NO"), 0;
    puts("YES");
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}