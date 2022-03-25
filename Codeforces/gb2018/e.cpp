#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

bool cmp(int x, int y) { return x > y; }
int n, a[maxn], b[maxn];
ll sum = 0;

int check(int x) {
    for (int i = 1; i <= n; i++) b[i] = a[i]; b[n + 1] = x;
    sort(b + 1, b + n + 2, cmp);
    int p = 0; for (int i = 1; i <= n + 1; i++) if (b[i] == x) p = i;
    ll sum = 0, s2 = 0; int j = n + 1;
    for (int i = 1; i <= n + 1; i++) {
        sum += b[i];
        while (j > i && b[j] <= i) s2 += b[j--];
        if (j < i) s2 -= b[i];
        if (sum > 1ll * i * (i - 1) + s2 + 1ll * i * max(j - i, 0)) {
            if (b[i] > x) return -1;
            else return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i), sum += a[i];
    sort(a + 1, a + 1 + n, cmp);
    sum %= 2;
    int l = 0, r = (n - sum) / 2, u = -1, d = -1;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(2 * m + sum) == -1) l = m + 1;
        else r = m - 1, d = m;
    }
    l = d, r = (n - sum) / 2;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(2 * m + sum) == 1) r = m - 1;
        else l = m + 1, u = m;
    }
    // cout << u << ' ' << d << endl;
    if (u == -1 || d == -1) return puts("-1"), 0;
    for (int i = d; i <= u; i++) printf("%d ", 2 * i + sum);
    return 0;
}