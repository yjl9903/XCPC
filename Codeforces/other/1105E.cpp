#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <string>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[50];
int n, m, p[50], G[50][50];
map<string,int> id;
map<int,int> mp;

int gid(string s) {
    static int tot = 0;
    if (id.count(s)) return id[s];
    return id[s] = ++tot;
}
void init() {
    for (auto& x: mp) {
        for (auto& y: mp) {
            if (x.first == y.first) continue;
            // G[id[x.first]][id[y.first]] = G[id[y.first]][id[x.first]] = 1;
            G[x.first][y.first] = G[y.first][x.first] = 1;
        }
    }
    mp.clear();
}

int vis[50];

int main() {
    scanf("%d%d", &n, &m);
    int op;
    while (n--) {
        scanf("%d", &op);
        if (op == 1) {
            init();
        } else if (op == 2) {
            scanf("%s", s);
            mp[gid(string(s))] = 1;
        }
    }
    init();
    int T = 10000, ans = 0;
    for (int i = 1; i <= m; i++) p[i] = i;
    while (T--) {
        random_shuffle(p + 1, p + 1 + m);
        ms(vis, 0);
        int res = 1; vis[1] = 1;
        for (int i = 2; i <= m; i++) {
            int flag = 1;
            for (int j = 1; j < i; j++) {
                if (vis[j] && G[p[i]][p[j]]) {
                    flag = 0; break;
                }
            }
            if (flag) {
                res++; vis[i] = 1;
            }
        }
        ans = max(ans, res);
    }
    cout << ans;
    return 0;
}