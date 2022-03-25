#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

int sg[maxn][maxn];

int getsg(int w, int h) {
    if (sg[w][h] != -1) return sg[w][h];
    vector<int> vis(1000, 0);
    for (int i = 2; i <= w / 2; i++) {
        vis[getsg(i, h) ^ getsg(w - i, h)] = 1;
    }
    for (int i = 2; i <= h / 2; i++) {
        vis[getsg(w, i) ^ getsg(w, h - i)] = 1;
    }
    for (int i = 0; i < 1000; i++) if (!vis[i]) return sg[w][h] = i;
}

int n, m;

int main() {
    ms(sg, -1);
    while (scanf("%d%d", &n, &m) == 2) {
        if (getsg(n, m)) puts("WIN");
        else puts("LOSE");
    }
    return 0;
}