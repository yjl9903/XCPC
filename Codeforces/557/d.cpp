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
const int maxn = 200000 + 5;

int n, m;
PII a[maxn], b[maxn];

bool check(int x) {
    if (x == n) return 0;
    for (int i = 1; i <= m; i++) {
        b[i].first = (a[i].first + x - 1) % n + 1;
        b[i].second = (a[i].second + x - 1) % n + 1;
        if (b[i].first > b[i].second) swap(b[i].first, b[i].second);
    }
    sort(b + 1, b + 1 + m);
    for (int i = 1; i <= m; i++) if (a[i] != b[i]) return 0;
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        if (a[i].first > a[i].second) swap(a[i].first, a[i].second);
    }
    sort(a + 1, a + 1 + m);
    for (int i = 1; i * i <= n; i++) {
        if (n % i) continue;
        if (check(i)) return puts("Yes"), 0;
        if (check(n / i)) return puts("Yes"), 0;
    }
    puts("No");
    return 0;
}