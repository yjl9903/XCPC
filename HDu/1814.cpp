#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;

vector<int> edge[maxn], ans;
int n, m, bel[maxn];

bool dfs(int x){
    if (bel[x]) return bel[x] % 2;
    bel[x] = 1; bel[x ^ 1] = 2;
    ans.push_back(x);
    for (auto& v : edge[x]){
        if (!dfs(v)) return false;
    }
    return true;
}

bool cal(){
    ms(bel, 0);
    for (int i = 0; i < 2 * n; i++){
        if (bel[i]) continue;
        ans.clear();
        if (!dfs(i)){
            for (int& x : ans) bel[x] = bel[x ^ 1] = 0;
            if (!dfs(i ^ 1)) return false;
        }
    }
    return true;
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        for (int i = 0; i <= 2 * n; i++) edge[i].clear();
        while (m--){
            int u, v; scanf("%d%d", &u, &v); u--; v--;
            edge[u].push_back(v ^ 1);
            edge[v].push_back(u ^ 1);
        }
        if (cal()){
            for (int i = 0; i < 2 * n; i++) if (bel[i] == 1) printf("%d\n", i + 1);
        }
        else puts("NIE");
    }
    return 0;
}