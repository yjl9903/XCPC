#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, pre[maxn], u[maxn], v[maxn], siz[maxn], cnt[maxn];

int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return ;
    pre[x] = y; siz[y] += siz[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", u + i, v + i);
        join(u[i], v[i]);
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        cnt[find(u[i])]++;
    }
    for (int i = 1; i <= n; i++) {
        if (i == find(i)) {
            ans += cnt[i] - siz[i] + 1;
        }
    }
    cout << ans;
    return 0;
}