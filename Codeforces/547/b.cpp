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
const int maxn = 400000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), a[n + i] = a[i];
    int ans = 0, tot = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (!a[i]) {
            tot = 0;
        } else {
            tot++;
            ans = max(ans, tot);
        }
    }
    cout << ans << endl;
    return 0;
}