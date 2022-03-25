#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, a[maxn], cnt[maxn], cl[maxn], cr[maxn];

struct Node {
    int l, r, c;
    bool operator<(const Node& b) const {
        if (l != b.l) return l < b.l;
        return r < b.r;
    }
};

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        cnt[a[i]]++; cr[a[i]] = i;
        if (cl[a[i]] == 0) cl[a[i]] = i;
    }
    vector<Node> v;
    for (int i = 1; i < maxn; i++) if (cnt[i]) {
        v.push_back({cl[i], cr[i], cnt[i]});
    }
    sort(v.begin(), v.end());
    int ans = 0, m = (int)v.size();
    for (int i = 0, j; i < m; i = j) {
        j = i; int rmx = v[i].r, mxc = v[i].c;
        while (j < m && v[j].l <= rmx) {
            rmx = max(rmx, v[j].r); 
            mxc = max(mxc, v[j].c);
            j++;
        }
        ans += rmx - v[i].l + 1 - mxc;
    }
    cout << ans;
    return 0;
}