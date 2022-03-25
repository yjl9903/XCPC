#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int vis[maxn], dis[maxn], N, K;

int bfs(){
    queue<int> q;
    q.push(N);  vis[N] = 1; dis[N] = 0;
    while (!q.empty()){
        int x = q.front();  q.pop();
        if (x == K)
            return dis[x];
        if (2 * x <= maxn && !vis[2 * x]){
            vis[2 * x] = 1;
            q.push(2 * x);
            dis[2 * x] = dis[x] + 1;
        }
        if (!vis[x + 1]){
            vis[x + 1] = 1;
            q.push(x + 1);
            dis[x + 1] = dis[x] + 1;
        }
        if (x - 1 >= 0 && !vis[x - 1]){
            vis[x - 1] = 1;
            q.push(x - 1);
            dis[x - 1] = dis[x] + 1;
        }
    }
}

int main(){
    while (cin >> N >> K){
        memset(vis, 0, sizeof vis);
        cout << bfs() << endl;
    }
    return 0;
}