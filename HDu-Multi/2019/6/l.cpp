#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], deg[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) deg[i] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (i > 1) deg[i / 2]++;
        }
        ll sa = 0, sb = 0;
        priority_queue<PII,vector<PII>,less<PII> > pq;
        for (int i = 1; i <= n; i++) if (deg[i] == 0) {
            pq.push({ a[i], i });
        }
        int t = 0;
        while (!pq.empty()) {
            PII u = pq.top(); pq.pop();
            if (t == 0) sa += u.first;
            else sb += u.first;
            t ^= 1;
            if (u.second > 1) {
                int fa = u.second / 2;
                deg[fa]--;
                if (deg[fa] == 0) pq.push({ a[fa], fa });
            }
        }
        printf("%lld %lld\n", sa, sb);
    }
    return 0;
}