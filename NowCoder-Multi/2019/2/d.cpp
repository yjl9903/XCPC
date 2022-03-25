#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <bitset>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef bitset<101> bs;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100 + 5;

struct node {
    int st; ll w; bs sta;
    bool operator<(const node& b) const {
        return w > b.w;
    }
};

int n, k, w[maxn];
char G[maxn][maxn];
bs s[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", w + i);
    for (int i = 1; i <= n; i++) {
        scanf("%s", G[i] + 1);
        for (int j = 1; j <= n; j++) if (G[i][j] == '1') s[i].set(j);
    }
    node a; a.w = 0; a.st = 1; a.sta.set();
    priority_queue<node> q; q.push(a);
    while (!q.empty()) {
        node x = q.top(); q.pop();
        k--; if (k == 0) return cout << x.w << '\n', 0;
        for (int i = x.st; i <= n; i++) {
            if (!x.sta.test(i)) continue;
            node nxt; nxt.sta = x.sta & s[i];
            nxt.w = x.w + w[i]; nxt.st = i + 1;
            q.push(nxt);
        }
    }
    puts("-1");
    return 0;
}