#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 2000 + 5;

int n, k, maxd; char s[maxn][maxn]; int vis[maxn][maxn];
string ans, tmp, st;
vector<PII> v;
vector<int> v2;

// void dfs(int i, int j, int d, int c, int flag){
//     if (d == 2 * n - 1) return;
//     if (c < k){
//         c += s[i][j] != 'a'; 
//         ans[d] = 'a';
//         dfs(i + 1, j, d + 1, c, flag);
//         dfs(i, j + 1, d + 1, c, flag);
//         return;
//     }
//     if (flag && s[i][j] > ans[d]) return;
    
// }

void dfs2(int i, int j, int c, int d){
    if (c == k && s[i][j] != 'a') {
        v.emplace_back(i, j); v2.push_back(d); maxd = max(d, maxd);
        return;
    }
    if (s[i][j] != 'a') c++;
    if (i + 1 < n && vis[i + 1][j] > c) {
        vis[i + 1][j] = c, dfs2(i + 1, j, c, d + 1);
    }
    if (j + 1 < n && vis[i][j + 1] > c) {
        vis[i][j + 1] = c, dfs2(i, j + 1, c, d + 1);
    }
}

void dfs(int i, int j, int d, int flag){
    if (d == 2 * n - 1) return;
    if (s[i][j] > tmp[d]) return;
    if (s[i][j] < tmp[d]) flag++;
    if (flag) tmp[d] = s[i][j];

    // cout << i << ' ' << j << ' ' << flag << ' ' << tmp << endl;

    if (i + 1 < n && j + 1 < n){
        if (s[i + 1][j] < s[i][j + 1]){
            dfs(i + 1, j, d + 1, flag);
        }
        else if (s[i + 1][j] > s[i][j + 1]){
            dfs(i, j + 1, d + 1, flag);
        }
        else {
            dfs(i + 1, j, d + 1, flag);
            dfs(i, j + 1, d + 1, flag);
        }
    }
    else if (i + 1 < n){
        dfs(i + 1, j, d + 1, flag);
    }
    else {
        dfs(i, j + 1, d + 1, flag);
    }
}

int main(){
    scanf("%d%d", &n, &k); maxd = k;
    if (k >= 2 * n - 1){
        for (int i = 0; i < 2 * n - 1; i++) putchar('a');
        return 0;
    }
    for (int i = 0; i < n; i++) scanf("%s", s[i]);

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) vis[i][j] = k + 1;
    dfs2(0, 0, 0, 0);

    for (int i = 0; i < 2 * n - 1; i++) st.push_back('z' + 1);
    for (int i = 0; i < maxd; i++) st[i] = 'a';
    ans = st;

    for (int i = 0; i < v.size(); i++){
        // cout << v[i].first << ' ' << v[i].second << ' ' << v2[i] << endl;
        if (v2[i] != maxd) continue;
        tmp = st;
        dfs(v[i].first, v[i].second, maxd, 1);
        ans = min(ans, tmp);
    }
    cout << ans;

    // for (int i = 0; i < n; i++){
    //     if (sx + i >= n || sy - i < 0) break;
    //     dfs(sx + i, sy - i, 0, 1);
    // }
    // for (int i = 0; i < k; i++) putchar('a');
    // cout << ans;

    return 0;
}