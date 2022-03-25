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

int n, x, a[maxn], first[maxn], last[maxn];
int mark[maxn], vis[maxn], r[maxn], l[maxn], cnt[maxn], sum[maxn];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= x + 1; i++) {
        r[i] = i; l[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (first[a[i]] == 0) first[a[i]] = i;
        last[a[i]] = i;
        sum[a[i]]++;
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
    // for (int i = 1; i <= x; i++) dbg(i, mark[i], r[i]);
    st.clear();
    for (int i = n; i >= 1; i--) {
        auto it = st.upper_bound(-a[i]);
        if (it != st.end()) {
            // dbg(i, a[i], *it);
            vis[-*it] = 1;
        }
        st.insert(-a[i]);
    }
    // for (int i = 1; i <= n; i++) dbg(i, vis[i]);
    int rp = x + 1;
    for (int i = x; i >= 1; i--) {
        if (vis[i]) break;
        rp = i;
    }
    first[x + 1] = n + 1;
    for (int i = x; i >= 1; i--) {
        if (first[i] == 0) first[i] = first[i + 1];
        first[i] = min(first[i], first[i + 1]);
        // dbg(i, first[i]);
    }
    for (int i = 1; i <= x; i++) last[i] = max(last[i], last[i - 1]);
    for (int i = rp; i <= x; i++) {
        cnt[first[i]]++;
    }
    for (int i = n; i >= 0; i--) {
        dbg(i, cnt[i]);
        cnt[i] += cnt[i + 1];
    }
    dbg(rp);
    ll ans = 1 + cnt[0];
    if (cnt[0] == n) ans--;
    int tot = 0;
    for (int i = 1; i <= x; i++) {
        if (mark[i]) break;
        dbg(i, last[i], cnt[last[i] + 1]);
        ans += 1 + cnt[last[i] + 1];
        // dbg(i, cnt[last[i] + 1]);
        tot += sum[i];
        if (tot + cnt[last[i] + 1] == n) ans--;
    }
    cout << ans << endl;
    return 0;
}