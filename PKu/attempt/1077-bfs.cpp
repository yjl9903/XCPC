#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <queue>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 362880 + 5;
const int HashSize = 5000003;

int head[HashSize], nxt[maxn], st[maxn][9], pre[maxn];
int dir[4] = {3, -3, 1, -1};
int map[3][3], sx, sy;

int Hash(int x[9]){
    int v = 0;
    for (int i = 0; i < 9; i++)
        v = v * 10 + x[i];
    return v % HashSize;
}
int insert(int t){
    int h = Hash(st[t]);
    int u = head[h];
    while (u){
        if (memcmp(st[u], st[t], sizeof(st[t])) == 0)
            return 0;
        u = nxt[u];
    }
    nxt[t] = head[h];
    head[h] = t;
    return 1;
}

void show(int x[9]){
    for (int i = 0; i < 9; i++){
        if (i && i % 3 == 0)
            cout << endl;
        cout << x[i] << ' ';
    }
    cout << endl << endl;
}

bool check(int tag, int src){
    if (tag < 0 || tag > 8)
        return false;
    if (tag / 3 == src / 3)
        return true;
    if (tag % 3 == src % 3)
        return true;
    return false;
}

int bfs(){
    queue<int> q;
    int cnt = 1, dst[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    insert(1); q.push(1);
    while (!q.empty()){
        int x = q.front(); q.pop();
        // show(st[x]);
        int tmp[9], ts = 0;
        if (memcmp(st[x], dst, sizeof dst) == 0)
            return x;
        for (int i = 0; i < 9; i++)
            if (st[x][i] == 0)
                ts = i;
        for (int i = 0; i < 4; i++){
            memcpy(tmp, st[x], sizeof tmp);
            int t = ts + dir[i];
            if (check(t, ts)){
                swap(tmp[t], tmp[ts]);
                memcpy(st[++cnt], tmp, sizeof tmp);
                if (insert(cnt)){
                    pre[cnt] = x;
                    q.push(cnt);
                }
                else{
                    cnt--;
                }
            }
        }
    }
    return 0;
}

int main(){
    char s[25];
    while (cin.getline(s, 30)){
        ms(head, 0); ms(pre, 0);
        stringstream ss(s);
        for (int i = 0; i < 9; i++){
            char x;
            ss >> x;
            if (x != 'x')
                st[1][i] = x - '0';
            else
                st[1][i] = 0;
            // cout << x << ' ';
        }
        // cout << endl;
        int flag = bfs();
        if (flag){
            vector<char> path;
            int u = pre[flag], f = flag;
            while (u){
                int t1, t2;
                for (int i = 0; i < 9; i++) if (st[u][i] == 0)
                    t1 = i;
                for (int i = 0; i < 9; i++) if (st[f][i] == 0)
                    t2 = i;
                if (t2 - t1 == 1)
                    path.push_back('r');
                if (t2 - t1 == -1)
                    path.push_back('l');
                if (t2 - t1 == 3)
                    path.push_back('d');
                if (t2 - t1 == -3)
                    path.push_back('u');
                f = u;
                u = pre[u];
            }
            for (int i = path.size() - 1; i >= 0; i--)
                cout << path[i];
            if (path.size())
                cout << endl;
        }
        else{
            cout << "unsolvable\n";
        }
    }
    return 0;
}