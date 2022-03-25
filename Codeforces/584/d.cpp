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

int n, k, pre[maxn];

int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return 1;
    pre[x] = y; return 0;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) pre[i] = i;
    int ans = 0;
    for (int i = 1, u, v; i <= k; i++) {
        scanf("%d%d", &u, &v);
        ans += join(u, v);
    }
    cout << ans;
    return 0;
}