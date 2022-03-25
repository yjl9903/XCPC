#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], ans[maxn], opt[maxn];
bool vis[maxn];
PII lim[maxn];
vector<int> lft[maxn], rht[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; i++) {
            lim[i].first = 1;
            lim[i].second = 2 * n;
            vis[i] = ans[i] = opt[i] = 0;
            lft[i].clear(); rht[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            // lim[abs(a[i])].second = n + i - 1;
            if (a[i] < 0) {
                lim[-a[i]].second = n + i - 1;
                opt[-a[i]] = -1;
            } else {
                lim[a[i]].second = n + i - 1;
                opt[a[i]] = 1;
            }
        }

        vector<int> stk1, stk2;
        auto get = [&](int x) -> int {
            int le = 1;
            int l = 0, r = (int)stk1.size() - 1, ans = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (-a[stk1[m]] > x) ans = stk1[m], l = m + 1;
                else r = m - 1;
            }
            if (ans != -1) le = n + ans;
            l = 0, r = (int)stk2.size() - 1, ans = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (a[stk2[m]] < x) ans = stk2[m], l = m + 1;
                else r = m - 1;
            }
            if (ans != -1) le = max(le, n + ans);
            return le;
        };
        for (int i = 1; i <= n; i++) {
            lim[abs(a[i])].first = get(abs(a[i]));
            if (a[i] < 0) {
                while (!stk1.empty() && a[i] < a[stk1.back()]) stk1.pop_back();
                stk1.push_back(i);
            } else {
                while (!stk2.empty() && a[i] < a[stk2.back()]) stk2.pop_back();
                stk2.push_back(i);
            }
        }
        for (int i = 1; i <= 2 * n; i++) {
            if (opt[i]) continue;
            lim[i].first = get(i);
        }

        for (int i = 1; i <= 2 * n; i++) {
            dbg(i, lim[i].first, lim[i].second);
        }

        for (int i = 1; i <= 2 * n; i++) {
            lft[lim[i].first].push_back(i);
            rht[lim[i].second].push_back(i);
        }
        set<int> st;
        int flag = 0;
        for (int i = 1; i <= 2 * n; i++) {
            for (int x: lft[i]) st.insert(x);
            int must = -1;
            for (int x: rht[i]) {
                if (vis[x]) continue;
                if (must == -1) must = x;
                else flag = 1;
            }
            if (flag) break;
            if (must != -1) ans[i] = must;
            else {
                ans[i] = *st.begin();
            }
            vis[ans[i]] = 1;
            st.erase(ans[i]);
        }
        if (flag) puts("-1");
        else {
            for (int i = 1; i <= 2 * n; i++) 
                printf("%d%c", ans[i], i == 2 * n ? '\n' : ' ');
        }
    }
    return 0;
}