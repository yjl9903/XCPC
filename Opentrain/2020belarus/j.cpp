#include<iostream>
#include<cstring>
#include <algorithm>
#include <cstdio>
#include<cmath>
#include<vector>
#include<queue>
using ll = long long;
using namespace std;
const int N = 3e5 + 10;
const int Mod = 0;
ll a[N];
int n,m,T;
int Read();
vector<int> G[N];
int vis[N],book[N],val[N];
int f[2];
void dfs(int x,int opt){
    vis[x] = 1;
    val[x] = opt;
    f[opt]++;
    for(auto v :G[x])
        if (!vis[v]) dfs(v,opt^1);
}
queue<int> que;
int check(int x){
    while(!que.empty()) que.pop();
    que.push(x);
    while(!que.empty())
    {
        x = que.front();que.pop();
        for (auto v : G[x]) {
            if (!book[v]) {
                que.push(v);
                book[v] = 1;
            }
            if (val[x] ^ val[v]) continue;
            else return 0;
        }
    }
    return 1;
}
int main() {
    n = Read(),m = Read();
    for(int i = 1; i <= m; i++){
        int x = Read(), y = Read();
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    int ans = 0;
    for(int i = 1; i <= n;i++)
        if (!vis[i]){
            f[0] = f[1] = 0;
            vis[i] = 1;
            dfs(i,0);
            if(!check(i)) {
                cout << "-1" << "\n";
                return 0;
            }
            ans += min(f[0],f[1]);
        }
    cout << ans <<"\n";
    return 0;
}

int Read()  {
    int val = 0, opt = 1; char ch;
    while (!isdigit(ch = getchar())) if (ch == '-') opt = -1;
    while (isdigit( ch )) (val *= 10) += ch - '0', ch = getchar();
    return val * opt;
}
