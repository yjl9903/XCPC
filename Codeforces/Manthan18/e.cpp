#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

vector<int> q;
vector<PII> edge[maxn];
int from[maxn], to[maxn], deg[maxn], vis[maxn];
int n, m, k, ans[maxn];

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; i++){
        scanf("%d%d", from + i, to + i);
        deg[from[i]]++; deg[to[i]]++;
        edge[from[i]].emplace_back(to[i], i);
        edge[to[i]].emplace_back(from[i], i);
    }
    for (int i = 1; i <= n; i++){
        if (deg[i] < k){
            q.push_back(i);
        }
    }
    int l = 0;
    for (int i = m - 1; i >= 0; i--){
        while (l < q.size()){
            int t = q[l];
            for (PII v : edge[t]){
                if (vis[v.second]) continue;
                vis[v.second] = 1;
                deg[v.first]--; deg[t]--;
                if (deg[v.first] == k - 1) q.push_back(v.first);
            }
            l++;
        }
        ans[i] = n - q.size();
        if (vis[i]) continue;
        vis[i] = 1; deg[from[i]]--; deg[to[i]]--;
        if (deg[from[i]] == k - 1) q.push_back(from[i]);
        if (deg[to[i]] == k - 1) q.push_back(to[i]);
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
    return 0;
}