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
const int maxn = 1000 + 5;

int f[20];

int sg[maxn], s[maxn];
int getsg(int x) {
    if (sg[x] != -1) return sg[x];
    vector<int> vis(maxn, 0);
    for (int i = 0; i <= 16 && f[i] <= x; i++) {
        vis[getsg(x - f[i])] = 1;
    }
    for (int i = 0; i < maxn; i++) if (!vis[i]) return sg[x] = i;
}

int main() {
    ms(sg, -1);
    f[0] = f[1] = 1;
    for (int i = 2; i <= 16; i++) f[i] = f[i - 1] + f[i - 2];
    int n, m, p;
    while (scanf("%d%d%d", &n, &m, &p) == 3) {
        if (n == 0 && m == 0 && p == 0) return 0;
        if (getsg(n) ^ getsg(m) ^ getsg(p)) puts("Fibo");
        else puts("Nacci");
    }
    return 0;
}