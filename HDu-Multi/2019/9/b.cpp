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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, k, nn, xx[maxn], yy[maxn], op[maxn];
vector<int> ql[maxn], qr[maxn], qu[maxn], qd[maxn];

struct BIT {
    int a[maxn];
    inline void clear() {
        for (int i = 0; i < maxn; i++) a[i] = 0;
    }
    inline int lowbit(int i) { return i & -i; }
    void update(int i, int x) {
        for (; i < maxn; i += i & -i) a[i] += x;
    }
    void update(int l, int r, int x) {
        update(l, x); update(r + 1, -x);
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
} f;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        ll ans = 1;
        vector<int> lsh;
        for (int i = 1; i <= k; i++) {
            char s[5];
            scanf("%d%d%s", xx + i, yy + i, s);
            lsh.push_back(xx[i]);
            lsh.push_back(yy[i]);
            if (s[0] == 'L') op[i] = 1;
            else if (s[0] == 'R') op[i] = 2;
            else if (s[0] == 'U') op[i] = 3;
            else if (s[0] == 'D') op[i] = 4;
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        nn = (int)lsh.size();
        for (int i = 1; i <= nn; i++) {
            ql[i].clear();
            qr[i].clear();
            qu[i].clear();
            qd[i].clear();
        }
        for (int i = 1; i <= k; i++) {
            xx[i] = lower_bound(lsh.begin(), lsh.end(), xx[i]) - lsh.begin() + 1;
            yy[i] = lower_bound(lsh.begin(), lsh.end(), yy[i]) - lsh.begin() + 1;
            dbg(xx[i], yy[i], op[i]);
            if (op[i] == 1) {
                ql[yy[i]].push_back(xx[i]);
            } else if (op[i] == 2) {
                qr[yy[i]].push_back(xx[i]);
            } else if (op[i] == 3) {
                qu[yy[i]].push_back(xx[i]);                
            } else {
                qd[yy[i]].push_back(xx[i]);
            }
        }

        f.clear();
        for (int i = 1; i <= nn; i++) {
            for (int x: ql[i]) {
                f.update(1, x, 1);
            }
            for (int x: qr[i]) {
                f.update(x, nn, 1);
            }
            for (int x: qd[i]) {
                dbg(x, i, f.query(x));
                ans += f.query(x);
            }
        }
        f.clear();
        for (int i = nn; i >= 1; i--) {
            for (int x: ql[i]) {
                f.update(1, x, 1);
            }
            for (int x: qr[i]) {
                f.update(x, nn, 1);
            }
            for (int x: qu[i]) {
                dbg(x, i, f.query(x));
                ans += f.query(x);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}