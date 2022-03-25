#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 500000 + 5;

struct node {
    int to; ll d;
    bool operator<(const node& b) const {
        return d > b.d;
    }
};

int n, mn = 1e9, vis[maxn];
ll bmn, bmx, dis[maxn];
vector<int> a;

ll cal(ll x) {
    ll ans = 0;
    for (int i = 0; i < mn; i++) {
        if (x < dis[i]) continue;
        ans += (x - dis[i]) / mn + 1;
    }
    return ans;
}

int main() {
    scanf("%d%lld%lld", &n, &bmn, &bmx);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        if (!x) continue;
        a.push_back(x); mn = min(mn, x);
    }
    for (int i = 1; i <= mn; i++) dis[i] = 1e18;
    priority_queue<node> q; q.push({0, 0}); dis[0] = 0;
    while (!q.empty()) {
        node tp = q.top(); q.pop();
        if (vis[tp.to]) continue;
        vis[tp.to] = 1;
        for (int& v: a) {
            int y = (v + tp.to) % mn;
            if (dis[y] > dis[tp.to] + v) {
                dis[y] = dis[tp.to] + v;
                q.push({y, dis[y]});
            }
        }
    }
    cout << cal(bmx) - cal(bmn - 1) << endl;
    return 0;
}