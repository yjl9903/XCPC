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
const int maxn = 2000000 + 5;

struct ACAM {
    static const int maxp = 200000 + 5;
    int ch[maxp][26], val[maxp], fail[maxp], sz;
    void clear() {
        sz = 1;
        ms(fail, 0); ms(val, 0); ms(ch, 0);
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    ACAM() {
        clear();
    }
    int match[maxp];
    void insert(char* s, int x) {
        int len = strlen(s), now = 1;
        for (int i = 0; i < len; i++) {
            int v = s[i] - 'a';
            if (!ch[now][v]) ch[now][v] = ++sz;
            now = ch[now][v];
        }
        match[x] = now;
        val[now] = x;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
    }
    vector<int> edge[maxp];
    int siz[maxp];
    void dfs(int u) {
        for (int& v: edge[u]) {
            dfs(v); siz[u] += siz[v];
        }
    }
    vector<int> query(int n, char* s) {
        int now = 1;
        for (int i = 0; s[i]; i++) {
            now = ch[now][s[i] - 'a'];
            siz[now]++;
        }
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
        dfs(1);
        vector<int> ans(1, 0);
        for (int i = 1; i <= n; i++) ans.push_back(siz[match[i]]);
        return ans;
    }
} f;

int n;
char s[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        f.insert(s, i);
    }
    f.build();
    scanf("%s", s);
    vector<int> ans = f.query(n, s);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}