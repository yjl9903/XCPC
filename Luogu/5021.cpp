#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 50000 + 5;

vector<PII> edge[maxn];
int n, m, tag, cnt;

int dfs(int u, int f) {
    // if (cnt >= m) return 0;
    deque<int> dq;
    multiset<int> st;
    for (auto& v: edge[u]) {
        if (v.first == f) continue;
        int x = dfs(v.first, u) + v.second;
        if (x >= tag) cnt++;
        // else dq.push_back(x);
        else st.insert(x);
    }

    int mx = 0;
    while (!st.empty()) {
        int tot = *st.begin(); st.erase(st.begin()); 
        auto it = st.lower_bound(tag - tot);
        if (it == st.end()) mx = max(mx, tot);
        else st.erase(it), cnt++;
    }
    return mx;
    // sort(dq.begin(), dq.end());
    // int mx = 0;
    // for (auto it = dq.begin(); it != dq.end(); it++) {
    //     auto p = lower_bound(it + 1, dq.end(), tag - *it);
    //     if (p == dq.end()) mx = max(*it, mx);
    //     else {
    //         dq.erase(p); cnt++;
    //     }
    // }
    // return mx;
}
int check(int x) {
    tag = x; cnt = 0;
    dfs(1, 0);
    return cnt >= m;
}

int main(){
    // freopen("track.in", "r", stdin);
    // freopen("track.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 2, u, v, l; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &l);
        edge[u].emplace_back(v, l);
        edge[v].emplace_back(u, l);
    }
    int l = 1, r = 1e9, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) l = m + 1, ans = m;
        else r = m - 1;
    }
    printf("%d\n", ans);
    return 0;
}