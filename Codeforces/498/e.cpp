#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, q, u, k, index, op[maxn], ed[maxn];
vector<int> line[maxn], v;

void dfs(int p){
    op[p] = ++index; v.push_back(p);
    for (int i = 0; i < line[p].size(); i++){
        dfs(line[p][i]);
    }
    ed[p] = index;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 2; i <= n; i++){
        int x; cin >> x;
        line[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) sort(line[i].begin(), line[i].end());
    v.push_back(0); dfs(1);
    while (q--){
        cin >> u >> k;
        if (ed[u] - op[u] + 1 < k) cout << -1 << endl;
        else cout << v[op[u] - 1 + k] << endl;
    }
    return 0;
}