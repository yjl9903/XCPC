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
const int maxn = 2000 + 5;

int n, k;
char s[maxn][maxn];
int lmx[maxn], rmx[maxn], umx[maxn], dmx[maxn];
int tans[maxn][maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            if (j > n || s[i][j] != 'W') {
                lmx[i] = j - 1; break;
            }
        }
        for (int j = n; j >= 0; j--) {
            if (j == 0 || s[i][j] != 'W') {
                rmx[i] = j + 1; break;
            }
        }
        for (int j = 1; j <= n + 1; j++) {
            if (j > n || s[j][i] != 'W') {
                umx[i] = j - 1; break;
            }
        }
        for (int j = n; j >= 0; j--) {
            if (j == 0 || s[j][i] != 'W') {
                dmx[i] = j + 1; break;
            }
        }
        dbg(i, lmx[i], rmx[i], umx[i], dmx[i]);
    }
    int ans = 0;
    for (int u = 1; u + k - 1 <= n; u++) {
        int d = u + k - 1;
        dbg(u, d);
        vector<int> tl, tr;
        for (int i = u; i <= d; i++) {
            tl.push_back(lmx[i]);
        }
        for (int i = u; i <= d; i++) {
            tr.push_back(rmx[i]);
        }
        sort(tl.begin(), tl.end());
        sort(tr.begin(), tr.end());
        reverse(tr.begin(), tr.end());
        int j = 0, sz = (int)tl.size();
        for (int l = 1; l + k - 1 <= n; l++) {
            while (j < sz && tl[j] < l) j++;
            tans[u][l] += sz - j + 1;
            dbg(u, l, sz - j + 1);
        }
        j = 0; sz = (int)tr.size();
        for (int r = n; r - k + 1 >= 1; r--) {
            while (j < sz && tr[j] > r) j++;
            tans[u][r - k + 1] += sz - j + 1;
        }
    }
    for (int l = 1; l + k - 1 <= n; l++) {
        int r = l + k - 1;
        vector<int> tu, td;
        for (int i = l; i <= r; i++) {
            tu.push_back(umx[i]);
        }
        for (int i = l; i <= r; i++) {
            td.push_back(dmx[i]);
        }
        sort(tu.begin(), tu.end());
        sort(td.begin(), td.end());
        reverse(td.begin(), td.end());
        int j = 0, sz = (int)tu.size();
        for (int u = 1; u + k - 1 <= n; u++) {
            while (j < sz && tu[j] < u) j++;
            tans[u][l] += sz - j + 1;
        }
        j = 0; sz = (int)td.size();
        for (int d = n; d - k + 1 >= 1; d--) {
            while (j < sz && td[j] > d) j++;
            tans[d - k + 1][l] += sz - j + 1;
        }
    }
    for (int i = 1; i + k - 1 <= n; i++) {
        for (int j = 1; j + k - 1 <= n; j++) {
            ans = max(ans, tans[i][j]);
        }
    }
    cout << ans;
    return 0;
}