#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<int> edge[maxn << 1];
set<int> eds[maxn << 1];
namespace sam {
    int sz, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        for (int i = 1; i <= sz; i++) {
            len[i] = link[i] = cnt[i] = 0;
            ms(ch[i], 0);
        }
        sz = last = 1;
    }
    int insert(int c) {
        int cur = ++sz, p = last; 
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++sz; 
                len[nq] = len[p] + 1; 
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    void build() {
        for (int i = 2; i <= sz; i++) edge[link[i]].push_back(i);
    }
}
using namespace sam;

int n, q, ans[maxn], b[maxn];
char s[maxn];

void update(int i, int x) {
    for (i = n - i + 1; i <= n; i += i & -i) b[i] = max(b[i], x);
}
int query(int i) {
    int r = 0;
    for (i = n - i + 1; i; i -= i & -i) r = max(r, b[i]);
    return r;
}

vector<PII> upd[maxn], que[maxn];

void dfs(int u) {
    for (int v: edge[u]) {
        dfs(v);
        if (!len[u]) continue;
        if ((int)eds[u].size() < (int)eds[v].size()) swap(eds[u], eds[v]);
        for (int p: eds[v]) {
            auto it = eds[u].upper_bound(p);
            if (it != eds[u].end()) {
                upd[*it].push_back({p, len[u]});
            }
            if (it != eds[u].begin()) {
                it--; upd[p].push_back({*it, len[u]});
            }
        }
        for (int p: eds[v]) eds[u].insert(p);
    }
}

int main() {
    sam::clear();
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 1; i <= n; i++) {
        eds[sam::insert(s[i] - '0')].insert(i);
    }
    sam::build();
    dfs(1);
    for (int i = 1, l, r; i <= q; i++) {
        scanf("%d%d", &l, &r);
        que[r].push_back({l, i});
    }
    for (int r = 1; r <= n; r++) {
        for (auto& q: upd[r]) {
            update(q.first, q.second);
        }
        for (auto& q: que[r]) {
            ans[q.second] = query(q.first);
        }
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}