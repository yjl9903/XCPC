#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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
const ll inf = 1ll << 60;
const int maxn = 3000000 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0; 
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}

int n, a[maxn], nxt[maxn][2];
ll pre[maxn];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
ll mx[maxn << 2], mn[maxn << 2];
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = mn[rt] = pre[l];
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
inline ll qmax(int L, int R, int l = 0, int r = n, int rt = 1) {
    assert(0 <= L && L <= R && R <= n);
    if (L <= l && r <= R) return mx[rt];
    int m = (l + r) / 2; ll ans = -inf;
    if (L <= m) ans = qmax(L, R, lson);
    if (R > m) ans = max(ans, qmax(L, R, rson));
    return ans;
}
inline ll qmin(int L, int R, int l = 0, int r = n, int rt = 1) {
    assert(0 <= L && L <= R && R <= n);
    if (L <= l && r <= R) return mn[rt];
    int m = (l + r) / 2; ll ans = inf;
    if (L <= m) ans = qmin(L, R, lson);
    if (R > m) ans = min(ans, qmin(L, R, rson));
    return ans;
}

int main() {
    n = gi();
    for (int i = 1; i <= n; i++) a[i] = gi();
    for (int i = 1; i <= n; i++) pre[i] = gi() + pre[i - 1];
    build(0, n, 1);
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] > a[i]) {
            nxt[st.back()][0] = i - 1; st.pop_back();
        }
        st.push_back(i);
    }
    for (int i = 1; i <= n; i++) if (!nxt[i][0]) nxt[i][0] = n;
    st.clear();
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && a[st.back()] > a[i]) {
            nxt[st.back()][1] = i + 1; st.pop_back();
        }
        st.push_back(i);
    }
    for (int i = 1; i <= n; i++) if (!nxt[i][1]) nxt[i][1] = 1;

    // for (int i = 1; i <= n; i++) {
    //     dbg(i,nxt[i][1], nxt[i][0]);
    // }

    ll ans = -inf;
    for (int i = 1; i <= n; i++) {
        int m = i, l = nxt[i][1], r = nxt[i][0];
        ll mx = qmax(m, r);
        ll mn = qmin(l - 1, m - 1);
        ans = max(ans, 1ll * a[i] * (mx - mn));
        mx = qmin(m, r);
        mn = qmax(l - 1, m - 1);
        ans = max(ans, 1ll * a[i] * (mx - mn));
    }
    cout << ans << endl;
    return 0;
}