#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

int n, root, val[maxn], ch[maxn][2], in[maxn], ans = 0;
set<int> st;

void dfs(int u, int mi, int mx){
    if (mi < val[u] && val[u] < mx) st.insert(val[u]);
    if (ch[u][0] != -1) dfs(ch[u][0], mi, min(mx, val[u]));
    if (ch[u][1] != -1) dfs(ch[u][1], max(mi, val[u]), mx);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d%d%d", &val[i], &ch[i][0], &ch[i][1]);
        if (ch[i][0] != -1) in[ch[i][0]]++;
        if (ch[i][1] != -1) in[ch[i][1]]++;
    }
    for (int i = 1; i <= n; i++) if (!in[i]){
        root = i; break;
    }
    dfs(root, -1, inf);
    for (int i = 1; i <= n; i++) if (!st.count(val[i])) ans++;
    printf("%d", ans);
    return 0;
}