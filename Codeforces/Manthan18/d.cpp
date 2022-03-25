#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

vector<int> edge[maxn];
int n, a[maxn], vis[maxn];

int bfs(){
    vis[1] = 1;
    int l = 0, s = 1; 
    while (l < s){
        int t = a[l];
        set<int> p, q;
        for (int v : edge[t]) if (!vis[v]) p.insert(v);
        for (int i = s; i < s + p.size(); i++) q.insert(a[i]);
        if (p != q) return 0;
        for (int i : p) vis[i] = 1;
        s += p.size(); l++; 
    }
    return 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 0, x, y; i < n - 1; i++){
        scanf("%d%d", &x, &y); 
        edge[x].push_back(y); edge[y].push_back(x);
    }
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    if (a[0] != 1) {puts("No"); return 0;}
    if (bfs()) puts("Yes");
    else puts("No");
    return 0;
}