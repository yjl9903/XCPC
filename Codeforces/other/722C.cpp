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

int n, op[maxn], pre[maxn], vis[maxn];
ll a[maxn], ans;

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return ;
    pre[y] = x; a[x] += a[y];
    ans = max(ans, a[x]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) pre[i] = i;
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", op + i);
    vector<ll> v;
    for (int i = n; i >= 1; i--) {
        v.push_back(ans);
        ans = max(ans, a[op[i]]);
        if (vis[op[i] - 1]) {
            join(op[i], op[i] - 1);
        }
        if (vis[op[i] + 1]) {
            join(op[i], op[i] + 1);
        }
        vis[op[i]] = 1;
    }
    reverse(v.begin(), v.end());
    for (ll& x: v) printf("%I64d\n", x);
    return 0;
}