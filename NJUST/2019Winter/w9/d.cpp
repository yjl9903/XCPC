#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, k, x;
ll a[maxn];

int main() {
    scanf("%d%d%d", &n, &k, &x);
    int zs = 0, ze = 0, fs = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", a + i);
        if (a[i] == 0) ze++;
        else if (a[i] > 0) zs++;
        else fs++;
    }
    if (ze) {
        if (ze > k) {
            printf("%I64d ", a[1] + 1ll * k * x);
            for (int i = 2; i <= n; i++) printf("%I64d ", a[i]);
            return 0;
        }
        int last = 0; 
        for (int i = 1; i <= n; i++) {
            if (a[i]) continue;
            a[i] += x; last = i;
        }
        if (fs % 2 == 0) a[last] = -x;
        tot = ze;
    }
    zs = 0, fs = 0;
    for (int i = 1; i <= n; i++) if (a[i] > 0) zs++; else fs++;
    if (fs % 2 == 0) {
        int m = 1e9 + 7, p = -1;
        for (int i = 1; i <= n; i++) {
            if (abs(a[i]) < m) m = abs(a[i]), p = i;
        }
        int mn = a[p];
        int cs = abs(m) / x + 1;
        if (cs + tot > k) {
            // set<PII> st;
            // for (int i = 1; i <= n; i++) st.insert({abs(a[i]), i});
            // for (; tot < k; tot++) {
            //     auto it = st.end(); it--;
            //     int id = it->second;
            //     if (a[id] < 0) a[id] += x;
            //     else a[id] -= x;
            //     st.erase(it);
            //     st.insert({abs(a[id]), id});
            // }
            // for (int i = 1; i <= n; i++) printf("%I64d ", a[i]);
            // return 0;
            int rest = k - tot;
            if (a[p] < 0) a[p] += 1ll * rest * x;
            else a[p] -= 1ll * rest * x;
            tot = k;
        } else {
            if (a[p] < 0) a[p] += 1ll * cs * x;
            else a[p] -= 1ll * cs * x;
            tot += cs;
        }
    }
    set<PII> st;
    for (int i = 1; i <= n; i++) st.insert({abs(a[i]), i});
    for (; tot < k; tot++) {
        auto it = st.begin();
        int id = it->second;
        if (a[id] < 0) a[id] -= x;
        else a[id] += x;
        st.erase(it);
        st.insert({abs(a[id]), id});
    }
    for (int i = 1; i <= n; i++) printf("%I64d ", a[i]);
    return 0;
}