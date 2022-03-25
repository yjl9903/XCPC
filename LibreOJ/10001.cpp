#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

struct node {
    int b, e, t;
    bool operator<(const node& y) const {
        return e != y.e ? e < y.e : b < y.b;
    }
} a[maxn];

int n, q, vis[maxn];

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 0; i < q; i++) scanf("%d%d%d", &a[i].b, &a[i].e, &a[i].t);
    sort(a, a + q);
    for (int i = 0; i < q; i++) {
        int cnt = 0;
        for (int j = a[i].b; j <= a[i].e; j++) cnt += vis[j];
        if (cnt >= a[i].t) continue;
        for (int j = a[i].e; j >= a[i].b; j--) {
            if (vis[j]) continue;
            vis[j] = 1; cnt++;
            if (cnt == a[i].t) break;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += vis[i];
    cout << ans << endl;
    return 0;
}