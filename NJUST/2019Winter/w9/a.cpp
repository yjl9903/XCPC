#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, t, c, a[maxn];

int main() {
    scanf("%d%d%d", &n, &t, &c);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    int len = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > t) {
            if (len >= c) ans += len - c + 1;
            len = 0;
        } else len++;
    }
    if (len >= c) ans += len - c + 1;
    cout << ans << endl;
    return 0;
}