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

int n, a[maxn], b[maxn];

int main() {
    scanf("%d", &n);
    int my = 0, dk = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] == 1) my = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", b + i);
        if (b[i] == 1) dk = i;
    }
    if (my) {
        int mx = 0;
        for (int i = 1; i <= n; i++) {
            if (b[i] == 0) continue;
            mx = max(mx, i - b[i] + 1);
        }
        printf("%d", mx + n);
    } else if (dk == n) {
        int f = 1;
        for (int i = 1; i < n; i++) {
            if (b[i] == 0) continue;
            if (b[i] - 2 < i) {
                f = 0; break;
            }
        }
        if (f) printf("%d", n - 1);
        else printf("%d", n + n);
    } else {
        int f = 1;
        for (int i = dk + 1; i <= n; i++) {
            if (b[i] == 0) {
                f = 0; break;
            }
            if (b[i] - b[i - 1] != 1) {
                f = 0; break;
            }
        }
        if (f) {
            int f = 1;
            int cur = n - dk + 1;
            for (int i = 1; i < dk; i++) {
                if (b[i] == 0) continue;
                // dbg(b[i], cur);
                if (b[i] - cur - 1 < i) {
                    f = 0; break;
                }
            }
            if (f) printf("%d", dk - 1);
            else printf("%d", n + dk);
        } else {
            int mx = 0;
            for (int i = dk + 1; i <= n; i++) {
                if (b[i] == 0) continue;
                // dbg(i - b[i] - dk + 1);
                mx = max(mx, i - b[i] - dk + 1);
            }
            // dbg(mx);
            printf("%d", dk + n + mx);
        }
    }
    return 0;
}