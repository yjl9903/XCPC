#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 5000 + 5;

int pre[maxn];
int find(int x){ return pre[x] == x ? x : pre[x] = find(pre[x]); }

int dis(PII a, PII b){
    int x = a.first - b.first, y = a.second - b.second;
    return abs(x) + abs(y);
}

int n, a, b;
PII s1, s2, p[maxn];
set<int> st[maxn];
vector<int> block[maxn];
bool G[maxn][maxn], vis[maxn]; int dis1[maxn], dis2[maxn];

int main(){
    scanf("%d%d%d%d%d%d%d", &n, &a, &b, &s1.first, &s1.second, &s2.first, &s2.second);
    for (int i = 0; i <= n; i++) pre[i] = i;
    for (int i = 0; i < n; i++) scanf("%d%d", &p[i].first, &p[i].second);
    for (int i = 0; i < a; i++) {
        int x, y; scanf("%d%d", &x, &y);
        st[x].insert(y); st[y].insert(x);
    }
    for (int i = 0; i < b; i++) {
        int x, y; scanf("%d%d", &x, &y);
        pre[find(x)] = find(y);
    }
    for (int i = 1; i <= n; i++) block[find(i)].push_back(i);
    for (int i = 1; i <= n; i++){
        if (block[i].empty()) continue;
        for (int k = 0; k < block[i].size(); k++){
            for (int j = k + 1; j < block[i].size(); j++){
                int x = block[i][k], y = block[i][j];
                if (st[x].count(y)) return puts("-1"), 0;
            }
        }
    }
    for (int i = 1; i <= n; i++){
        int mx1 = 0, mx2 = 0;
        for (int x : block[i]){
            mx1 = max(mx1, dis(p[x], s1));
            mx2 = max(mx2, dis(p[x], s2));
        }
        dis1[i] = mx1; dis2[i] = mx2;
    }
    for (int i = 1; i <= n; i++){
        for (int x : st[i]){
            G[pre[i]][pre[x]] = G[pre[x]][pre[i]] = 1;
        }
    }
    for (int i = 1; i <= n; i++){
        if (block[i].empty()) continue;
        
    }

    return 0;
}