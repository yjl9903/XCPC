#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int root[maxn], ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40];

int n, x, a[maxn], first[maxn], last[maxn];
int mark[maxn], vis[maxn], r[maxn], l[maxn];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= x + 1; i++) {
        r[i] = i; l[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (first[a[i]] == 0) first[a[i]] = i;
        last[a[i]] = i;
    }
    set<int> st;
    for (int i = 1; i <= n; i++) {
        auto it = st.upper_bound(a[i]);
        if (it != st.end()) {
            r[a[i]] = *it + 1;
            mark[*it] = 1;
        }
        st.insert(a[i]);
    }
    // for (int i = 1; i <= x; i++) dbg(i, r[i]);
    st.clear(); st.insert(a[n]);
    for (int i = n - 1; i >= 1; i--) {
        auto it = st.begin();
        if (*it < a[i]) {
            l[a[i]] = min(l[a[i]], *it - 1);
        }
        // it = st.lower_bound(a[i]);
        // if (it != st.begin()) {
        //     if (it == st.end() || *it == a[i]) it--;
        //     dbg(i, a[i], *it);
        //     if (*it < a[i]) vis[*it] = 1;
        // }
        st.insert(a[i]);
    }
    // for (int i = 1; i <= x; i++) dbg(i, mark[i]);
    // for (int i = 1; i <= x; i++) dbg(i, vis[i]);
    int rp = n + 1;
    for (int i = n; i >= 1; i--) {
        if (vis[i]) break;
        rp = i;
    }
    for (int i = rp; i <= x + 1; i++) dbg(i, l[i]);
    dbg(rp);
    ll ans = 0;
    for (int i = 0; i <= x; i++) {
        if (mark[i]) break;
        dbg(i, r[i]);
        for (int i = max(rp, r[i]); i <= x + 1; i++) {
            if (l[i] >= i) ans++;
        }
        dbg(i, ans);
    }
    cout << ans << endl;
    return 0;
}