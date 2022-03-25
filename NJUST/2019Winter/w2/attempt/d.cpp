#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200 + 5;

char t[maxn], tmp[maxn]; 
int n, len, a[maxn], cnt[maxn][26], allc[26];
int mn = 1e9, vis[maxn];

void dfs(int p, int r) {
    if (p == len) mn = min(r, mn);
    if (r >= mn) return;
    if (allc[t[p] - 'a'] == 0) return;

    for (int i = 0; i < n; i++) {
        if (vis[i] >= a[i]) continue;
        if (cnt[i][t[p] - 'a'] == 0) continue;
        vis[i]++; cnt[i][t[p] - 'a']--; allc[t[p] - 'a']--;
        dfs(p + 1, r + i + 1);
        vis[i]--; cnt[i][t[p] - 'a']++; allc[t[p] - 'a']++;
    }
}

int main(){
    scanf("%s%d", t, &n); len = strlen(t);
    for (int i = 0; i < n; i++) {
        scanf("%s%d", tmp, a + i);
        int l = strlen(tmp);
        for (int j = 0; j < l; j++) cnt[i][tmp[j] - 'a']++, allc[tmp[j] - 'a']++;
    }
    // for (int i = 0; i < n; i++, puts("")) for (int j = 0; j < 26; j++) printf("%d ", cnt[i][j]);
    dfs(0, 0);
    if (mn == (int)1e9) return puts("-1"), 0;
    cout << mn << endl;
    return 0;
}