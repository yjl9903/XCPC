#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int maxn = 300000 + 5;

char s[maxn];
int n;
vector<int> p[2];

int getnxt(int x, int t) {
    int it = upper_bound(p[t].begin(), p[t].end(), x) - p[t].begin();
    if (it == (int)p[t].size()) return -1;
    return p[t][it];
}

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for (int i = 1; i <= n; i++) p[s[i] - '0'].push_back(i);
    ll ans = 0;
    int last = 0;
    for (int i = 0; i + 2 < (int)p[0].size(); i++) {
        int a = p[0][i], b = p[0][i + 1], c = p[0][i + 2];
        if (b - a == c - b) {
            ans += 1ll * (a - last) * (n - c + 1);
            last = a;
        }
    }
    last = 0;
    for (int i = 0; i + 2 < (int)p[1].size(); i++) {
        int a = p[1][i], b = p[1][i + 1], c = p[1][i + 2];
        if (b - a == c - b) {
            ans += 1ll * (a - last) * (n - c + 1);
            last = a;
        }
    }
    last = 0;
    for (int i = 1; i <= n; i++) {
        int a0, b0, c0;
        int a1, b1, c1;
        if (s[i] == '0') a0 = i, a1 = getnxt(i, 1);
        else a0 = getnxt(i, 0), a1 = i;
        if (a0 == -1 || a1 == -1) break;
        b0 = getnxt(a0, 0);
        b1 = getnxt(a1, 1);
        if (b0 == -1 || b1 == -1) break;
        c0 = getnxt(b0, 0);
        c1 = getnxt(b1, 1);
        if (c0 == -1 || c1 == -1) break;
        // dbg(a0, b0, c0);
        // dbg(a1, b1, c1);
        if (b0 - a0 == c0 - b0 && b1 - a1 == c1 - b1) {
            int l = min(a0, a1), r = max(c0, c1);
            ans -= 1ll * (l - last) * (n - r + 1);
            last = l;
        }
    }
    cout << ans;
    return 0;
}