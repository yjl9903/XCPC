#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

vector<int> hv[maxn], lsh;
vector<PII> v;
ll suf[maxn];
int n, m, h[maxn];

int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

int rt[maxn], ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40], tot; ll sum[maxn * 40];
void update(int p, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    cnt[rt] = cnt[pre] + 1; sum[rt] = sum[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (p <= m) update(p, x, ls[pre], lson);
    else update(p, x, rs[pre], rson);
}
ll query(int k, int l, int r, int rt) {
    if (cnt[rt] <= k) return sum[rt];
    if (l == r) return 1ll * sum[rt] / cnt[rt] * k;
    int m = (l + r) >> 1;
    if (cnt[ls[rt]] >= k) return query(k, lson);
    else return sum[ls[rt]] + query(k - cnt[ls[rt]], rson);
}

int main(){
    ms(h, -1);
    scanf("%d%d", &n, &m);
    for (int i = 1, a, c; i <= m; i++) {
        scanf("%d%d", &a, &c);
        hv[c].push_back(a);
        lsh.push_back(a);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    int toti = lsh.size();
    for (int i = 1; i <= n; i++) {
        sort(hv[i].begin(), hv[i].end(), [](int x, int y){return x>y;});
        for (int j = 0; j < hv[i].size(); j++) {
            v.push_back({j, hv[i][j]});
        }
    }
    sort(v.begin(), v.end());
    // cout << "hhh:\n";
    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i].first << ' ' << v[i].second << endl;
    // }
    suf[v.size()] = 0;
    for (int i = v.size() - 1; i >= 0; i--) suf[i] = suf[i + 1] + v[i].second;
    for (int i = 0; i < v.size(); i++) {
        if (h[v[i].first] == -1) {
            h[v[i].first] = i;
        }
        update(gid(v[i].second), v[i].second, rt[i], 1, toti, rt[i + 1]);
        // dbg();
    }
    for (int i = 1; i <= m; i++) if (h[i] == -1) h[i] = v.size();
    // cout << "h[i]\n";
    // for (int i = 0; i <= m; i++) {
    //     cout << h[i] << endl;
    // }
    ll ans = suf[0];
    for (int i = 1; i <= m; i++) {
        ll t = suf[h[i - 1]];
        int c = m - h[i - 1];
        if (i > c) {
            // dbg(i, h[i - 1]);
            t += query(i - c, 1, toti, rt[h[i - 1]]);
        }
        ans = min(ans, t);
        // dbg(i, suf[h[i - 1]], t - suf[h[i - 1]]);
    }
    printf("%lld\n", ans);
    return 0;
}