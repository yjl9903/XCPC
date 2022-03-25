#include <iostream>
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
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
vector<int> ans;
int n, m, vis[maxn];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v); 
        edge[u].push_back(v); edge[v].push_back(u);
    }
    priority_queue<int> pq; pq.push(-1); vis[1] = 1;
    while (!pq.empty()) {
        int t = -pq.top(); pq.pop();
        ans.push_back(t);
        for (int& v: edge[t]) {
            if (vis[v]) continue;
            pq.push(-v); vis[v] = 1;
        }
    }
    for (int& x: ans) printf("%d ", x);
    return 0;
}