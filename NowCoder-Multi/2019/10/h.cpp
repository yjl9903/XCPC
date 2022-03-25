#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<PII> cg[5];
vector<int> degs[5];
char res[][30] = {
    "n-hexane", "2-methylpentane",
    "3-methylpentane", "2,3-dimethylbutane",
    "2,2-dimethylbutane"
};
int vis[5][10][10], p[20], deg[10];
void init() {
    cg[0] = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6} };
    cg[1] = { {1, 2}, {2, 3}, {2, 4}, {4, 5}, {5, 6} };
    cg[2] = { {1, 2}, {2, 3}, {3, 4}, {3, 5}, {5, 6} };
    cg[3] = { {1, 2}, {2, 3}, {2, 4}, {4, 5}, {4, 6} };
    cg[4] = { {1, 2}, {2, 3}, {2, 4}, {2, 5}, {5, 6} };
    for (int i = 0; i < 5; i++) {
        for (auto& x: cg[i]) {
            vis[i][x.first][x.second] = vis[i][x.second][x.first] = 1;
        }
    }

    degs[0] = { 1, 1, 2, 2, 2, 2 };
    degs[1] = { 1, 1, 1, 2, 2, 3 };
    degs[2] = { 1, 1, 1, 2, 2, 3 };
    degs[3] = { 1, 1, 1, 1, 3, 3 };
    degs[4] = { 1, 1, 1, 1, 2, 4 };
}

int main() {
    init();
    mt19937 rnd(time(0));
    int T; scanf("%d", &T);
    while (T--) {
        ms(deg, 0);
        vector<PII> G;
        for (int i = 1, u, v; i <= 5; i++) {
            scanf("%d%d", &u, &v);
            G.push_back({u, v});
            deg[u]++; deg[v]++;
        }
        vector<int> v;
        for (int i = 1; i <= 6; i++) v.push_back(deg[i]);
        sort(v.begin(), v.end());

        int ans = -1;
        
        auto check = [&](int tp) {
            if (v != degs[tp]) return ;
            vector<int> chk(5, 1);
            for (int i = 1; i <= 6; i++) p[i] = i;
            do {
                for (int i = 0; i < 5; i++) chk[i] = 1;
                for (auto& x: G) {
                    int u = p[x.first], v = p[x.second];
                    for (int i = 0; i < 5; i++) {
                        if (!vis[i][u][v]) chk[i] = 0;
                    }
                }
                for (int i = 0; i < 5; i++) if (chk[i]) {
                    ans = i; break;
                }
            } while (ans == -1 && next_permutation(p + 1, p + 7));
        };

        if (v == degs[0]) ans = 0;
        else if (v == degs[3]) ans = 3;
        else if (v == degs[4]) ans = 4;
        else {
            check(1);
            if (ans == -1) ans = 2;
        }

        assert(ans != -1);
        printf("%s\n", res[ans]);
    }
    return 0;
}