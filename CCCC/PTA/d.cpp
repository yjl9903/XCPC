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
const int maxn = 100000 + 5;

int pre[maxn];
int n, q;

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
int join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return 0;
    pre[x] = y; return 1;
}

int main() {
    for (int i = 0; i < maxn; i++) pre[i] = i;
    int mx = 1;
    scanf("%d", &n);
    while (n--) {
        int k, x, last; scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d", &x);
            if (i == 0) last = x;
            else {
                join(last, x);
            }
            mx = max(mx, x);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= mx; i++) if (pre[i] == i) cnt++;
    printf("%d %d\n", mx, cnt);
    scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d%d", &u, &v);
        if (find(u) == find(v)) puts("Y");
        else puts("N");
    }
    return 0;
}