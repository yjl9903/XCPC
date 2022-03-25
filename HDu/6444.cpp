#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const ll inf = 1ll << 60;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n, m, k, g, rd, ansl, ansr, a[maxn], q[maxn * 2];
ll s, pre[maxn]; vector<int> v;
bool vis[maxn];

ll cal(int len){
    if (len == 0) return 0;
    int l = 1, r = 0; ll mx = -inf; ansl = ansr = 0;
    for (int i = 1; i < v.size(); i++){
        while (l <= r && pre[i - 1] < pre[q[r]]) r--;
        q[++r] = i - 1;
        while (i - q[l] > len) l++;
        if (pre[i] - pre[q[l]] > mx){
            mx = pre[i] - pre[q[l]];
            ansl = q[l] + 1; ansr = i;
        }
    }
    return mx;
}
ll get(int beg){
    int sz = v.size(); ll sum = 0;
    for (int i = 1; i < sz; i++) v.push_back(v[i]), sum += v[i];
    for (int i = 1; i < v.size(); i++) pre[i] = pre[i - 1] + v[i];
    sum = max(pre[rd], 0ll);
    ll ans1 = 1ll * m / rd * sum + cal(m % rd);
    ll ans2 = -inf;
    if (m >= rd){
        ll x = cal(rd);
        ans2 = 1ll * (m - ansr + ansl - 1) / rd * sum + x;
    }
    return max(ans1, ans2);
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ms(vis, 0);
        scanf("%d%lld%d%d", &n, &s, &m, &k);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        g = gcd(n, k); rd = n / g;
        ll mx = -inf;
        for (int i = 0; i < n; i++){
            if (vis[i]) continue;
            int j = i; v.clear(); v.push_back(0);
            while (!vis[j]) vis[j] = 1, v.push_back(a[j]), j = (j + k) % n;
            mx = max(mx, get(i));
        }
        printf("Case #%d: %lld\n", ++kase, max(0ll, s - mx));
    }
    return 0;
} 