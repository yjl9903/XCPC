#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m, dis[maxn];

int main() {
    ms(dis, -1);
    cin >> n >> m;
    queue<int> q; q.push(n); dis[n] = 0;
    while (!q.empty()) {
        int tp = q.front(); q.pop();
        if (tp == m) return printf("%d", dis[m]), 0;
        if (dis[tp * 2] == -1) {
            dis[tp * 2] = dis[tp] + 1;
            q.push(tp * 2);
        }
        if (tp > 1 && dis[tp - 1] == -1) {
            dis[tp - 1] = dis[tp] + 1;
            q.push(tp - 1);
        }
    }
    assert(0);
    return 0;
}