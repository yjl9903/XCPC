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

int n, a[maxn];

int main() {
    scanf("%d", &n); int mx = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mx = max(mx, a[i]);
    int ans = 1, i = 1;
    while (i <= n) {
        if (a[i] != mx) i++;
        else {
            int j = i;
            while (j <= n && a[j] == mx) j++;
            ans = max(ans, j - i);
            i = j;
        }
    }
    cout << ans << endl;
    return 0;
}