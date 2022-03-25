#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 50000 + 5;

vector<PII> edge[maxn];
int n, m, tag;

vector<int> pa[maxn];
void dfs(int u, int f, int tp, int tl) {
    int tot = tl, p = -1;
    if (tl >= tag) pa[tp].push_back(tl), tl = 0, tp = u;
    else {
        for (auto& v: edge[u]) {
            if (v.first == f) continue;
            if (tot < tag) {
                if (tl + v.second > tot) {
                    tot = tl + v.second;
                    p = v.first;
                }
            } else {
                if (tl + v.second < tot) {
                    tot = tl + v.second;
                    p = v.first;
                }
            }
        }
        if (p != -1) dfs(p, u, tp, tot);
        else pa[tp].push_back(tot);
    }
    for (auto& v: edge[u]) {
        if (v.first == f || v.first == p) continue;
        dfs(v.first, u, u, v.second);
    }
}
int check(int x) {
    tag = x; for (int i = 1; i <= n; i++) pa[i].clear();
    dfs(1, 0, 1, 0);
    // cout << x << " : \n";
    // for (int i = 1; i <= n; i++) {
    //     cout << i << " = ";
    //     for (int x: pa[i]) cout << x << ' ';
    //     cout << endl;
    // }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> v;
        deque<int> dq;
        for (int& x: pa[i]) {
            if (x >= tag) v.push_back(x), cnt++;
            else dq.push_back(x);
        }
        sort(dq.begin(), dq.end());
        while ((int)dq.size() >= 2) {
            int x = dq.front() + dq.back();
            if (x < tag) dq.pop_front();
            else {
                cnt++;
                dq.pop_front(); dq.pop_back();
            }
        }
    }
    return cnt >= m;
}

int main(){
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