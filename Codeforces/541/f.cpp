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
const int maxn = 200000 + 5;

int n, pre[maxn], head[maxn], nxt[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) pre[i] = head[i] = i;
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        int x = find(u), y = find(v);
        pre[y] = x;
        nxt[head[x]] = y;
        head[x] = head[y];
    }
    for (int i = 1; i <= n; i++) if (pre[i] == i) {
        int tot = i;
        while (tot) {
            printf("%d ", tot); tot = nxt[tot];
        }
    }
    return 0;
}