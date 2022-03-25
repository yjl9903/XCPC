#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

vector<int> b[maxn];
int n, m, vis[maxn], tot;

int deg[maxn], pre[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i;
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        deg[u]++; deg[v]++;
        pre[find(u)] = find(v);
    }
    for (int i = 1; i <= n; i++) b[find(i)].push_back(i);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int flag = 1;
        for (int& x: b[i]) {
            if (deg[x] != 2) {
                flag = 0; break;
            }
        }
        if (flag && (int)b[i].size() >= 3) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}