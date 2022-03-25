#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 200000 + 5;

int n, k, a[maxn];
PII b[maxn]; int tot;

int check(int x) {
    int l = 1, r = 1, c = 0;
    while (r <= n) {
        if (a[r] - x <= a[l] + x) {
            r++; c++;
            if (c == k + 1) {
                tot = a[l] + x;
                return 1;
            }
        } else {
            l++; c--;
        }
    }
    return 0;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        if (k == 0) {
            printf("%d\n", a[1]); continue;
        }
        int l = 1, r = 1e9, ans = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m)) r = m - 1, ans = tot;
            else l = m + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}