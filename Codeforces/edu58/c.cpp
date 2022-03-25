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

struct node {
    int l, r, id;
    bool operator<(const node& b) const {
        if (l == b.l) return r < b.r;
        return l < b.l;
    }
} a[maxn];

int n, ans[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i, ans[i] = 0;
        sort(a, a + n);
        int r = a[0].r, flag = 1; ans[a[0].id] = 1;
        for (int i = 1; i < n; i++) {
            if (a[i].l > r) {
                flag = 0; break;
            }
            ans[a[i].id] = 1;
            r = max(r, a[i].r);
        }
        if (flag) {
            puts("-1"); continue;
        }
        for (int i = 0; i < n; i++) if (ans[i]) printf("1 "); else printf("2 ");
        puts("");
    }
    return 0;
}