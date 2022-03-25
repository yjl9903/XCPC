#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10 + 5;

int vis[maxn][maxn], dis[maxn][maxn];
int dir[8][2] = {1, 2, -1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, 1, -2, -1};
PII beg, dst;

int bfs(){
    memset(vis, 0, sizeof vis);
    queue<PII> q;
    q.push(beg);    vis[beg.first][beg.second] = 1; dis[beg.first][beg.second] = 0;
    while (!q.empty()){
        PII x = q.front();  q.pop();
        if (x == dst)   return dis[x.first][x.second];
        for (int i = 0; i < 8; i++){
            PII t = make_pair(x.first + dir[i][0], x.second + dir[i][1]);
            if (t.first >= 0 && t.second >= 0 && t.first < 8 && t.second < 8 && !vis[t.first][t.second]){
                vis[t.first][t.second] = 1;
                dis[t.first][t.second] = dis[x.first][x.second] + 1;
                q.push(t);
            }
        }
    }
}

int main(){
    char xx[5], yy[5];
    while (cin >> xx >> yy){
        beg.first = xx[0] - 'a';    beg.second = xx[1] - '1';
        dst.first = yy[0] - 'a';    dst.second = yy[1] - '1';
        cout << "To get from " << xx << " to " << yy << " takes " << bfs() << " knight moves." << endl;
    }
    return 0;
}