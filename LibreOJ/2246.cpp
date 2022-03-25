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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int fail[maxn], ans[maxn];
char s[maxn];

vector<int> edge[maxn];
void getfail() {
    fail[1] = 0;
    for (int i = 2; s[i]; i++) {
        int cur = fail[i - 1];
        while (cur && s[cur + 1] != s[i]) cur = fail[cur];
        if (s[cur + 1] == s[i]) cur++;
        fail[i] = cur;
    }
}

vector<int> stk;
void dfs(int u) {
    if (u) {
        auto it = upper_bound(stk.begin(), stk.end(), u / 2);
        it--;
        ans[u] = it - stk.begin();
    }
    stk.push_back(u);
    for (int v: edge[u]) {
        dfs(v);
    }
    stk.pop_back();
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        getfail();
        int n = strlen(s + 1);
        for (int i = 0; i <= n; i++) edge[i].clear();
        for (int i = 1; i <= n; i++) edge[fail[i]].push_back(i);
        dfs(0);
        // for (int i = 1; i <= n; i++) cout << i << " : " << ans[i] << endl;
        int res = 1;
        for (int i = 1; i <= n; i++) res = 1ll * res * (ans[i] + 1) % mod;
        printf("%d\n", res);
    }
    return 0;
}