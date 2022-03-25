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
const int maxn = 200000 + 5;

int n, a[maxn], suf[maxn][2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = n; i >= 1; i--) {
        suf[i][i % 2] = a[i] + suf[i + 1][i % 2];
        suf[i][(i + 1) % 2] = suf[i + 1][(i + 1) % 2];
    }
    int a = 0, b = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            if (a + suf[i + 1][0] == b + suf[i + 1][1]) ans++;
            a += ::a[i];
        } else {
            if (a + suf[i + 1][0] == b + suf[i + 1][1]) ans++;
            b += ::a[i];
        }
    }
    cout << ans << endl;
    return 0;
}