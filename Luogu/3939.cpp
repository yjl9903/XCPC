#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, m, a[maxn];
vector<int> bag[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), bag[a[i]].push_back(i);
    int op, l, r, x, c;
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &l, &r, &c);
            int st = lower_bound(bag[c].begin(), bag[c].end(), l) - bag[c].begin();
            int ed = upper_bound(bag[c].begin(), bag[c].end(), r) - bag[c].begin();
            printf("%d\n", ed - st);
        } else if (op == 2) {
            scanf("%d", &x);
            if (a[x] == a[x + 1]) continue;
            int p1 = lower_bound(bag[a[x]].begin(), bag[a[x]].end(), x) - bag[a[x]].begin();
            int p2 = lower_bound(bag[a[x + 1]].begin(), bag[a[x + 1]].end(), x + 1) - bag[a[x + 1]].begin();
            bag[a[x]][p1] = x + 1;
            bag[a[x + 1]][p2] = x;
            swap(a[x], a[x + 1]);
        }
    }
    return 0;
}
