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
const int maxn = 500000 + 5;

int n, a[maxn], nxt[maxn][2];
ll pre[maxn];

ll mx[maxn][20], mn[maxn][20];
void init() {
    for (int i = 0; i <= n; i++) mx[i][0] = mn[i][0] = pre[i];
    for (int j = 1; j < 20; j++)
        for (int i = 0; i + (1 << j) <= n + 1; i++) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
}
ll qmax(int l, int r) {
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}
ll qmin(int l, int r) {
    int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = a[i] + pre[i - 1];
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
        dbg(i,nxt[i][0], nxt[i][1]);
    }

    ll ans = 0;
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