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
const int inf = 1 << 30;
const int maxn = 1100000 + 5;

int n, q, m;
char s[maxn];

namespace gsam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][2];
    int insert(int last, int c) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        return cur;
    }
    namespace Trie {
        int tot, ch[maxn][2], pos[maxn];
        void clear() {
            tot = 1;
        }
        void insert(char* s) {
            int u = 1;
            for (int i = 0; s[i]; i++) {
                int c = s[i] - '0';
                if (!ch[u][c]) {
                    ch[u][c] = ++tot;
                    ms(ch[tot], 0);
                }
                u = ch[u][c];
            }
        }
        void build() {
            queue<int> q; q.push(1);
            pos[1] = 1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < 2; i++) {
                    if (!ch[u][i]) continue;
                    int v = ch[u][i];
                    pos[v] = gsam::insert(pos[u], i);
                    q.push(v);
                }
            }
        }
    }
    using Trie::insert;
    using Trie::build;
    void clear() { 
        Trie::clear();
        tot = last = 1; 
    }

    int dp[maxn], q[maxn];
    bool check(int x) {
        dp[0] = 0;
        int l = 1, r = 0, u = 1, mx = 0;
        for (int i = 1; i <= n; i++) {
            int c = s[i] - '0';
            if (ch[u][c]) u = ch[u][c], mx++;
            else {
                while (u && !ch[u][c]) u = link[u];
                if (!u) u = 1, mx = 0;
                else mx = len[u] + 1, u = ch[u][c];
            }

            dp[i] = dp[i - 1];
            int tl = i - mx, tr = i - x;
            if (tr < 0) continue;
            while (l <= r && dp[tr] - tr >= dp[q[r]] - q[r]) r--;
            q[++r] = tr;
            while (l <= r && q[l] < tl) l++;

            if (l <= r) dp[i] = max(dp[i], i + dp[q[l]] - q[l]);
        }
        return 10 * dp[n] >= 9 * n;
    }
}

int main() {
    gsam::clear();
    scanf("%d%d", &q, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", s);
        gsam::insert(s);
    }
    gsam::build();
    while (q--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        int l = 0, r = n, ans = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (gsam::check(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}