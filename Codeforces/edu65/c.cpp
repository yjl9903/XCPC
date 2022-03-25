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
const int maxn = 500000 + 5;

int n, m;
int pre[maxn], siz[maxn];
int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return ;
    pre[x] = y; siz[y] += siz[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1;
    for (int i = 1, k, x; i <= m; i++) {
        scanf("%d", &k);
        if (k == 0) continue;
        scanf("%d", &x); k--;
        while (k--) {
            int y; scanf("%d", &y);
            join(x, y);
        }
    }
    for (int i = 1; i <= n; i++) cout << siz[find(i)] << ' ';
    return 0;
}