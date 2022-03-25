#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}

int n, m, f[maxn], g[maxn], suf[maxn], col[maxn][maxn];
char s[maxn][maxn];

struct BIT {
    int a[maxn];
    void clear() {
        for (int i = 1; i <= m; i++) a[i] = 0;
    }
    void update(int i, int x) {
        for (; i <= m; i += i & -i) a[i] = add(a[i], x);
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r = add(r, a[i]);
        return r;
    }
    int query(int l, int r) {
        return sub(query(r), query(l - 1));
    }
} h;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; j++) if (s[i][j] == 'R') col[i][j] = 1;
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            col[i][j] += col[i + 1][j];
        }
    }
    int c = 0;
    for (int i = 1; i <= m; i++) if (s[1][i] == 'R') c++;
    for (int i = 1; i <= m - c; i++) f[i] = 1;
    for (int i = 2; i <= n; i++) {
        h.clear();
        for (int j = 1; j <= m; j++) {
            if (col[i][j] == n - i + 1) continue;
            h.update(j, f[j]);
        }
        for (int j = m; j >= 1; j--) {
            suf[j] = suf[j + 1];
            if (s[i][j] == 'R') suf[j]++;
        }
        vector<int> rock;
        for (int j = 1; j <= m; j++) {
            if (suf[j] == m - j + 1) {
                if (col[i][j] == n - i + 1) {
                    f[j] = 0;
                } else {
                    // f[j] = query(j, j);
                    f[j] = 0;
                    g[j] = h.query(j, j);
                }
            } else if (s[i][j] == 'R') {
                int l = 1, r = j;
                if (col[i][j] == n - i + 1) r--;
                int rest = m - j - suf[j + 1] - 1;
                int p = (int)rock.size() - rest - 1;
                if (p >= 0) l = rock[p] + 1;
                f[j] = query(l, r);
                rock.push_back(i);
            } else {
                int l = 1, r = j;
                int rest = m - j - suf[j + 1];
                int p = (int)rock.size() - rest - 1;
                if (p >= 0) l = rock[p] + 1;
                f[j] = h.query(l, r);
            }
        }
    }
    cout << f[m];
    return 0;
}