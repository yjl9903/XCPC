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
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, deg[maxn], flag = 0;

void dfs(int u) {
    if (flag) return;
    int cnt = 0;
    for (int& v: edge[u]) {
        if (deg[v] == 0) cnt++;
        else dfs(v);
    }
    if (cnt < 3) flag = 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int x; scanf("%d", &x);
        deg[x]++; 
        edge[x].push_back(i);
    }
    dfs(1);
    if (flag) puts("No");
    else puts("Yes");
    return 0;
}