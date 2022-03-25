#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 300000 + 5;

int n, t, a[maxn], p[maxn];
PII gs[maxn];
set<PII> dates[maxn];

namespace SegT {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1

    struct Info {
        int mn, day;
        Info operator+(const Info& b) const {
            if (mn <= b.mn) return (Info){mn, day};
            else return (Info){b.mn, b.day};
        }
    } b[maxn << 2];

    void build(int l, int r, int rt) {
        if (l == r) {
            if (a[l]) b[rt] = (Info){0, l};
            else b[rt] = (Info){inf, l};
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        b[rt] = b[rt << 1] + b[rt << 1 | 1];
    }
    void update(int i, int l = 1, int r = t, int rt = 1) {
        if (l == r) {
            assert(a[i] > 0);
            b[rt].mn = dates[i].begin()->first;
            return ;
        }
        int m = (l + r) / 2;
        if (i <= m) update(i, lson);
        else update(i, rson);
        b[rt] = b[rt << 1] + b[rt << 1 | 1];
    }
    Info query(int L, int R, int l = 1, int r = t, int rt = 1) {
        if (L <= l && r <= R) return b[rt];
        int m = (l + r) / 2;
        if (R <= m) return query(L, R, lson);
        else if (L > m) return query(L, R, rson);
        else return query(L, R, lson) + query(L, R, rson);
    }
}
using SegT::update;
using SegT::query;

ll ans = 0;
set<int> st;
void getpos(int l, int r, int val, int id) {
    auto it = st.lower_bound(l);
    if (it != st.end()) {
        int pos = *it;
        dates[pos].insert({val, id}); update(pos);
        if ((int)dates[pos].size() == a[pos]) {
            st.erase(it);
        }
        ans += val;
    } else {
        SegT::Info qres = query(l, r);
        if (qres.mn >= val) return ;
        ans -= qres.mn; ans += val;
        int id = dates[qres.day].begin()->second;
        dates[qres.day].erase(dates[qres.day].begin());
        dates[qres.day].insert({val, id});
        update(qres.day);
        getpos(gs[id].first, gs[id].second, p[id], id);
    }
}

int main() {
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", a + i);
        if (a[i]) st.insert(i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &gs[i].first, &gs[i].second, p + i);
    }
    SegT::build(1, t, 1);
    for (int i = 1; i <= n; i++) {
        getpos(gs[i].first, gs[i].second, p[i], i);
    }
    cout << ans;
    return 0;
}
