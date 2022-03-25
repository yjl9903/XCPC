#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int x[3], y[3];
bool vis[maxn][maxn];

vector<PII> get(int x, int y, int xx, int yy) {
    vector<PII> v1, v2;
    for (int i = min(x, xx); i <= max(x, xx); i++) {
        if (!vis[i][y]) v1.push_back({i, y});
        if (!vis[i][yy]) v2.push_back({i, yy});
    }
    for (int i = min(y, yy); i <= max(y, yy); i++) {
        if (!vis[xx][i] && i != y) v1.push_back({xx, i});
        if (!vis[x][i] && i != yy) v2.push_back({x, i});
    }
    return (v1.size() < v2.size()) ? v1 : v2;
}

vector<PII> cal(int i, int j, int k) {
    int tx = x[i], ty = y[j];
    vector<PII> tmp; ms(vis, 0);
    for (int c = min(tx, x[j]); c <= max(tx, x[j]); c++) if (c != tx) tmp.push_back({c, ty}), vis[c][ty] = 1;
    for (int c = min(ty, y[i]); c <= max(ty, y[i]); c++) if (c != ty) tmp.push_back({tx, c}), vis[tx][c] = 1;

    // dbg(x[i], y[i]); dbg(x[j], y[j]); dbg(tx, ty);
    // for (auto& x: tmp) cout << x.first << ' ' << x.second << endl;
    // cout << "+\n";

    vector<PII> v = get(tx, ty, x[k], y[k]);
    // for (auto& x: v) cout << x.first << ' ' << x.second << endl;
    // cout << endl;
    for (auto& x: v) tmp.push_back(x);
    return tmp;
}

int main(){
    for (int i = 0; i < 3; i++) scanf("%d%d", x + i, y + i);
    if (x[0] == x[1] && x[1] == x[2]) {
        int l = min(y[0], min(y[1], y[2])), r = max(y[0], max(y[1], y[2]));
        printf("%d\n", r - l + 1);
        for (int i = l; i <= r; i++) printf("%d %d\n", x[0], i);
        return 0;
    }
    if (y[0] == y[1] && y[1] == y[2]) {
        int l = min(x[0], min(x[1], x[2])), r = max(x[0], max(x[1], x[2]));
        printf("%d\n", r - l + 1);
        for (int i = l; i <= r; i++) printf("%d %d\n", i, y[0]);
        return 0;
    }

    vector<PII> ans; int sz = 1e9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            vector<PII> t = cal(i, j, 3 - i - j);
            if (t.size() < sz) ans = t, sz = t.size();
        }
    }

    printf("%d\n", sz);
    for (auto& x: ans) {
        printf("%d %d\n", x.first, x.second);
    }
    return 0;
}