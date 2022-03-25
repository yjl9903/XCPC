#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstring>
#define PII pair<int,int>
using namespace std;
const int maxn = 105;

int s, n, m, res = 0, vis[maxn][maxn];


int bfs(){
    int cnt;
    queue<PII> Q;
    queue<int> Q2;
    vis[0][0] = 1;
    PII x = make_pair(0, 0), y;
    Q.push(x);  Q2.push(0);
    while (!Q.empty()){
        x = Q.front();
        Q.pop();
        vis[x.first][x.second] = 1;
        int rest = s - x.first - x.second;
        cnt = Q2.front();
        Q2.pop();
        if (x.first == s / 2 && rest == s / 2)
            return cnt;
        //cout << x.first << ' ' << x.second << ' ' << rest << endl;
        //cout << "cnt=" << cnt << endl;

        if (rest + x.first >= n){
            if (!vis[n][x.second])
                y = make_pair(n, x.second), Q.push(y), Q2.push(cnt + 1);
        }
        else if (!vis[rest + x.first][x.second])
            y = make_pair(rest + x.first, x.second), Q.push(y), Q2.push(cnt + 1);

        if (rest + x.second >= m){
            if (!vis[x.first][m])
                y = make_pair(x.first, m), Q.push(y), Q2.push(cnt + 1);
        }
        else if (!vis[x.first][x.second + rest])
            y = make_pair(x.first, x.second + rest), Q.push(y), Q2.push(cnt + 1);

        if (!vis[x.first][0])
            y = make_pair(x.first, 0), Q.push(y), Q2.push(cnt + 1);
        if (!vis[0][x.second])
            y = make_pair(0, x.second), Q.push(y), Q2.push(cnt + 1);

        // n -> m
        if (x.first + x.second >= m){
            if (!vis[x.first + x.second - m][m])
                y = make_pair(x.first + x.second - m, m), Q.push(y), Q2.push(cnt + 1);
        }
        else if (!vis[0][x.first + x.second])
            y = make_pair(0, x.first + x.second), Q.push(y), Q2.push(cnt + 1);

        // m -> n
        if (x.first + x.second >= n){
            if (!vis[n][x.first + x.second - n])
                y = make_pair(n, x.first + x.second - n), Q.push(y), Q2.push(cnt + 1);
        }
        else if (!vis[x.first + x.second][0])
            y = make_pair(x.first + x.second, 0), Q.push(y), Q2.push(cnt + 1);
    }
    return 0;
}

int main(){
    while (cin >> s >> n >> m && s && n && m){
        if (s % 2)  {cout << "NO" << endl; continue;}
        memset(vis, 0, sizeof vis);
        if (n < m)  swap(n, m);
        int res = bfs();
        if (res)
            cout << res << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
