#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 3000000 + 5;

vector<int> edge1[maxn], edge[maxn], leaf;
int n, p[maxn], dep[maxn], vis[maxn];

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    int flag = 1;
    for (int& v: edge1[u]) {
        if (v == f) continue;
        flag = 0;
        dfs1(v, u);
    }
    if (flag) {
        leaf.push_back(u);
    }
}

void dfs(int u, int f) {
    int flag = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        flag = 0;
        dfs(v, u);
    }
    if (flag) {
        printf("%d\n", u);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) scanf("%d", p + i), edge1[p[i]].push_back(i);
    dfs1(1, 0); sort(leaf.begin(), leaf.end());
    for (int& x: leaf) {
        int k = x;
        while (p[k]) {
            if (vis[k]) break;
            edge[p[k]].push_back(k);
            vis[k] = 1;
            k = p[k];
        }
    }
    dfs(1, 0);
    
    return 0;
}