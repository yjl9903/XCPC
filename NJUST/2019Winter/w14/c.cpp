#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 1000000 + 5;

int n, ch[maxn][2], ans[maxn], a[maxn];
char tp[maxn];

int dfs(int u) {
    if (tp[u] == 'I') return a[u];
    if (tp[u] == 'N') return a[u] = (dfs(ch[u][0]) ^ 1);
    if (tp[u] == 'A') return a[u] = (dfs(ch[u][0]) & dfs(ch[u][1]));
    if (tp[u] == 'O') return a[u] = (dfs(ch[u][0]) | dfs(ch[u][1]));
    if (tp[u] == 'X') return a[u] = (dfs(ch[u][0]) ^ dfs(ch[u][1]));
    assert(0);
}
void dfs2(int u, int flag, int num) {
    // cout << u << ' ' << flag << ' ' << num << endl;
    if (tp[u] == 'I') {
        if (flag) ans[u] = a[1];
        else {
            if (num % 2 == 0) ans[u] = a[u] ^ 1;
            else ans[u] = a[u];
        }
        return ;
    }
    if (tp[u] == 'N') {
        dfs2(ch[u][0], flag, num + 1);
    }
    if (tp[u] == 'A') {
        if (a[ch[u][1]] == 0) dfs2(ch[u][0], 1, num);
        else dfs2(ch[u][0], flag, num);
        if (a[ch[u][0]] == 0) dfs2(ch[u][1], 1, num);
        else dfs2(ch[u][1], flag, num);
    }
    if (tp[u] == 'O') {
        if (a[ch[u][1]] == 1) dfs2(ch[u][0], 1, num);
        else dfs2(ch[u][0], flag, num);
        if (a[ch[u][0]] == 1) dfs2(ch[u][1], 1, num);
        else dfs2(ch[u][1], flag, num);
    }
    if (tp[u] == 'X') {
        if (a[ch[u][1]] == 1) dfs2(ch[u][0], flag, num + 1);
        else dfs2(ch[u][0], flag, num);
        if (a[ch[u][0]] == 1) dfs2(ch[u][1], flag, num + 1);
        else dfs2(ch[u][1], flag, num);
    }
}

int main() {
    ms(ans, -1);
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++) {
        char s[5]; scanf("%s%d", s, &x);
        if (s[0] == 'I') {
            tp[i] = 'I'; a[i] = x; continue;
        }
        if (s[0] == 'N') {
            tp[i] = 'N'; ch[i][0] = x; continue;
        }
        tp[i] = s[0];
        scanf("%d", &y);
        ch[i][0] = x; ch[i][1] = y;
    }
    dfs(1); 
    
    // for (int i = 1; i <= n; i++) cout << i << ": " << a[i] << endl;
    
    dfs2(1, 0, 0);
    for (int i = 1; i <= n; i++) if (ans[i] != -1) printf("%d", ans[i]);
    return 0;
}