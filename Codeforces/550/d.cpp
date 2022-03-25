#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn]; map<int,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mp[a[i]]++;
    int mx = -1, x = 0, p;
    for (auto& it: mp) if (it.second > mx) mx = it.second, x = it.first;
    for (int i = 1; i <= n; i++) if (a[i] == x) p = i;
    printf("%d\n", n - mx);
    if (n == mx) return 0;
    for (int i = p - 1; i >= 1; i--) {
        if (a[i] == x) continue;
        if (a[i] < a[i + 1]) putchar('1');
        else putchar('2');
        printf(" %d %d\n", i, i + 1);
        a[i] = x;
    }
    for (int i = p + 1; i <= n; i++) {
        if (a[i] == x) continue;
        if (a[i] < a[i - 1]) putchar('1');
        else putchar('2');
        printf(" %d %d\n", i, i - 1);
        a[i] = x;
    }
    return 0;
}