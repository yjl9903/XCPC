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
const int maxn = 100000 + 5;

int n, m, a[maxn], b[maxn], c[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        multiset<int> st;
        vector<PII> ev;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", a + i, b + i);
            ev.push_back({a[i], -i});
            ev.push_back({b[i], i});
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d", c + i);
            ev.push_back({c[i], 0});
        }
        sort(ev.begin(), ev.end());
        int ans = 0, f = 1;
        for (auto& x: ev) {
            if (x.second == 0) {
                // dbg(st.size());
                if (st.empty()) {
                    f = 0; break;
                }
                ans = max(ans, n - (int)st.size() + 1);
                st.erase(st.begin());
            } else if (x.second > 0) {
                int id = x.second;
                // dbg(id, a[id], b[id]);
                if (st.count(b[id])) st.erase(st.find(b[id]));
            } else {
                int id = -x.second;
                // dbg(a[id], x.first);
                st.insert(b[id]);
            }
        }
        printf("Case #%d: ", ++kase);
        if (!f) puts("IMPOSSIBLE!");
        else printf("%d\n", ans);
    }
    return 0;
}