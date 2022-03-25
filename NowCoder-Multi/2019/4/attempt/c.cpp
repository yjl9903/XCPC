#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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

int mx[22][maxn], mn[22][maxn];
void init() {
    for (int i = 0; i <= n; i++) mx[0][i] = mn[0][i] = i;
    for (int j = 1; j < 22; j++)
        for (int i = 0; i + (1 << j) <= n + 1; i++) {
            // mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
            // mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
            int a = mx[j - 1][i], b = mx[j - 1][i + (1 << (j - 1))];
            if (pre[a] > pre[b]) mx[j][i] = a;
            else mx[j][i] = b;
            a = mn[j - 1][i], b = mn[j - 1][i + (1 << (j - 1))];
            if (pre[a] < pre[b]) mn[j][i] = a;
            else mn[j][i] = b;
        }
}
ll qmax(int l, int r) {
    int k = __lg(r - l + 1);
    int a = mx[k][l], b = mx[k][r - (1 << k) + 1];
    if (pre[a] > pre[b]) return pre[a];
    else return pre[b];
}
ll qmin(int l, int r) {
    int k = __lg(r - l + 1);
    int a = mn[k][l], b = mn[k][r - (1 << k) + 1];
    if (pre[a] < pre[b]) return pre[a];
    else return pre[b];
}

int main() {
    n = gi();
    for (int i = 1; i <= n; i++) a[i] = gi();
    for (int i = 1; i <= n; i++) pre[i] = gi() + pre[i - 1];
    init();
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

    for (int i = 1; i <= n; i++) {
        dbg(i,nxt[i][1], nxt[i][0]);
    }

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