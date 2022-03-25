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
const int maxn = 100000 + 5;

int n, a[maxn], b[maxn], vis[maxn][2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int l1 = -1, r1 = -1, cnt1 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        if (l1 == -1) l1 = i;
        r1 = i;
        cnt1++;
    }
    int l2 = -1, r2 = -1, cnt2 = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) continue;
        if (l2 == -1) l2 = i;
        r2 = i;
        cnt2++;
    }
    if (l1 == -1) {
        cout << r2 - l2 + 1 - cnt2 << endl; return 0;
    }
    if (l2 == -1) {
        cout << r1 - l1 + 1 - cnt1 << endl; return 0;
    }
    int ans = r1 - l1 + 2 + r2 - l2;
    if (l2 >= r1) ans = r2 - l1 + 2 - cnt1 - cnt2;
    else if (l1 >= r2) ans = r1 - l2 + 2 - cnt1 - cnt2;
    else {
        int cnt3 = 0, cnt4 = 0;
        for (int i = max(l1, l2) + 1; i < min(r1, r2); i++) {
            if (a[i] == 0) cnt3++;
            if (b[i] == 0) cnt4++;
        }
        // dbg(ans, cnt3, cnt4, cnt1 + cnt2);
        ans = min(ans - cnt3, ans - cnt4);
        ans -= cnt1 + cnt2;
    }
    cout << ans << endl;
    return 0;
}