#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

struct edge {
    int u, v; ll d;
    bool operator<(const edge& b) const {
        return d > b.d;
    }
};

int n, m, pre[maxn];
ll a[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main(){
    scanf("%d%d", &n, &m); for (int i = 1; i <= n; i++) pre[i] = i;
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    priority_queue<edge> q;
    while (m--) {
        int x, y; ll d; scanf("%d%d%I64d", &x, &y, &d);
        q.push({x, y, d});
    }
    ll mn = 1e18; int id = 0;
    for (int i = 1; i <= n; i++) if (a[i] < mn) mn = a[i], id = i;
    for (int i = 1; i <= n; i++) if (i != id) q.push({i, id, a[i] + a[id]});
    ll ans = 0; int cnt = 0;
    while (!q.empty() && cnt < n - 1) {
        edge t = q.top(); q.pop();
        if (find(t.u) == find(t.v)) continue;
        ans += t.d;
        pre[find(t.u)] = find(t.v);
        cnt++;
    }
    cout << ans;
    return 0;
}