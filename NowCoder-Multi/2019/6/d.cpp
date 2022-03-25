#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <cassert>
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

int n, k, v[maxn];

int check(int x) {
    multiset<int> st;
    for (int i = 1; i <= n; i++) st.insert(v[i]);
    if (*st.rbegin() > x) return false;
    int c = 1, tot = x;
    while (!st.empty()) {
        auto it = st.upper_bound(tot);
        if (it == st.begin()) {
            c++; tot = x;
            if (c > k) return false;
        }
        it = st.upper_bound(tot);
        assert(it != st.begin());
        it--;
        tot -= *it;
        st.erase(it);
    }
    return true;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        int l = 0, r = 1e6, ans = -1;
        for (int i = 1; i <= n; i++) scanf("%d", v + i), l = max(l, v[i]);
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m)) ans = m, r = m - 1;
            else l = m + 1;
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}