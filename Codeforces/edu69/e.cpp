#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int add(int& x, int y) {
    return (x += y) >= mod ? x -= mod : x;
}

struct Info {
    ll mn = inf; int cnt = 0;
    Info(ll a = inf, int b = 0) {
        mn = a; cnt = b;
    }
} tr[maxn];
void join(Info& a, Info b) {
    if (a.mn > b.mn) a.mn = b.mn, a.cnt = b.cnt;
    else if (a.mn == b.mn) add(a.cnt, b.cnt);
}
void update(int i, Info x) {
    for (; i < maxn; i += i & -i) join(tr[i], x);
}
Info query(int i) {
    Info x;
    for (; i; i -= i & -i) join(x, tr[i]);
    return x;
}

int n;
PII a[maxn];

int main() {
    scanf("%d", &n);
    vector<int> lsh; lsh.push_back(-1);
    int mxin = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].second, &a[i].first);
        lsh.push_back(a[i].first); lsh.push_back(a[i].second);
        mxin = max(mxin, a[i].first);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    sort(a + 1, a + 1 + n);
    update(1, (Info){ 0ll, 1 });
    Info ans;
    for (int i = 1; i <= n; i++) {
        int tin = lower_bound(lsh.begin(), lsh.end(), a[i].first) - lsh.begin() + 1;
        int tout = lower_bound(lsh.begin(), lsh.end(), a[i].second) - lsh.begin() + 1;
        Info tot = query(tin);
        tot.mn += a[i].first - a[i].second;
        update(tout, tot);
        if (a[i].second > mxin) tot.mn += a[i].second, join(ans, tot);
    }
    cout << ans.cnt;
    return 0;
}