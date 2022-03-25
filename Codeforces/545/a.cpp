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

int n, a[maxn], suf[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = n; i >= 1; i--) {
        if (a[i] == 2) suf[i] = suf[i + 1] + 1;
        else suf[i] = 0;
    }
    int ans = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            tot++;
            ans = max(ans, min(tot, suf[i + 1]));
        } else tot = 0;
    }
    reverse(a + 1, a + 1 + n);
    for (int i = n; i >= 1; i--) {
        if (a[i] == 2) suf[i] = suf[i + 1] + 1;
        else suf[i] = 0;
    }
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            tot++;
            ans = max(ans, min(tot, suf[i + 1]));
        } else tot = 0;
    }
    cout << ans * 2 << endl;
    return 0;
}