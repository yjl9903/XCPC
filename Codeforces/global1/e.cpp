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

int n, c[maxn], t[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", c + i);
    for (int i = 0; i < n; i++) scanf("%d", t + i);
    if (c[0] != t[0] || c[n - 1] != t[n - 1]) return puts("No"), 0;
    for (int i = n - 1; i > 0; i--) c[i] -= c[i - 1];
    for (int i = n - 1; i > 0; i--) t[i] -= t[i - 1];
    sort(c + 1, c + n); sort(t + 1, t + n);
    for (int i = 1; i < n; i++) if (c[i] != t[i]) return puts("No"), 0;
    puts("Yes");
    return 0;
}