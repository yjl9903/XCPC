#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <queue>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector< vector<int> > VVI;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ull change(VVI mp) {
    ull state = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state |= ull(mp[3 - i][3 - j]) << (i * 16 + j * 4);
        }
    }
    return state;
}
VVI change(ull state) {
    VVI mp(4, vector<int>(4, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mp[3 - i][3 - j] = (state >> (i * 16 + j * 4)) & 15;
        }
    }
    return mp;
}
void print(VVI mp) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // cout << mp[i][j] << ' ';
            printf("%2d ", mp[i][j]);
        }
        cout << '\n';
    }
    puts("");
}

int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
unordered_map<ull,int> dep;
void init() {
    ull st = 0x123456789ABCDEF0;
    dep[st] = 0;
    queue<ull> q; 
    q.push(st);
    while (!q.empty()) {
        ull tot = q.front(); q.pop();
        int step = dep[tot];
        if (step == 20) continue;
        VVI tmp = change(tot);
        int tx, ty;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tmp[i][j] == 0) {
                    tx = i; ty = j; 
                }
            }
        }
        // dbg(tx, ty);
        dbg(step);
        print(tmp);
        for (int i = 0; i < 4; i++) {
            int x = tx + dir[i][0], y = ty + dir[i][1];
            if (x < 0 || y < 0 || x >= 4 || y >= 4) continue;
            swap(tmp[tx][ty], tmp[x][y]);
            ull state = change(tmp);
            swap(tmp[tx][ty], tmp[x][y]);
            if (dep.count(state)) continue;
            dep[state] = step + 1;
            q.push(state);
        }
    }
}

int main() {
    init();
    dbg("OK");
    // int T; scanf("%d", &T);
    // while (T--) {
    //     VVI mp(4, vector<int>(4, 0));
    //     for (int i = 0; i < 4; i++) {
    //         for (int j = 0; j < 4; j++) {
    //             scanf("%d", &mp[i][j]);
    //         }
    //     }
    //     // cout << change(mp) << endl;
    //     // print(change(change(mp)));
    // }
    return 0;
}