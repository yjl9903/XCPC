#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
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
const int maxn = 100000 + 5;

int n, q, a[maxn], b[maxn];
int pre[maxn];

int g(int l, int r) {
    if ((r - l + 1) % 2 == 0) return 0;
    return b[r] ^ b[l - 2];
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        a[0] = b[0] = pre[0] = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] ^= a[i - 1];
        for (int i = 1; i <= n; i++) b[i] = b[i - 1] ^ a[i];
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[max(i - 2, 0)] ^ b[i];
        }
        scanf("%d", &q);
        while (q--) {
            int l, r; scanf("%d%d", &l, &r);
            int le = r - l;
            int f1 = (le / 2 + 1) & 1, f2 = (le / 2 + (le % 2)) & 1;
            int ans = 0;
            // map<int,int> mp;
            // for (int i = l; i <= r; i++) for (int j = i; j <= r; j++) {
            //     if ((j - i + 1) % 2) {
            //         mp[j]++; mp[i - 2]++;
            //     }
            // }
            // dbg(l, r);
            // dbg(le / 2 + 1, le / 2 + le % 2);
            // for (auto& x: mp) {
            //     dbg(x.first, x.second);
            //     if (x.second % 2 == 1 && x.first >= 0) {
            //         ans ^= b[x.first];
            //     }
            // }
            if (f1) {
                ans ^= pre[max(l - 4, 0)];
                int rr = r;
                if ((r - l) % 2) rr--;
                // dbg(1, l - 2, rr);
                ans ^= pre[rr];
            }
            if (f2) {
                ans ^= pre[max(l - 3, 0)];
                int rr = r;
                if ((r - l) % 2 == 0) rr--;
                // dbg(2, l - 1, rr);
                ans ^= pre[rr];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}