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

int n, a[maxn], dp[maxn], pos[maxn], ans[2][maxn];

void get(int* ans) {
    int res = 1; dp[1] = a[1];
    for (int i = 2; i <= n; i++){
        if (a[i] > dp[res]) dp[++res] = a[i], pos[i] = res;
        else {
            int k = lower_bound(dp + 1, dp + 1 + res, a[i]) - dp;
            dp[k] = a[i]; pos[i] = k;
        }
    }
    int tot = res, mx = 1e9;
    for (int i = n; i >= 1 && tot >= 1; i--) {
        if (pos[i] == tot && mx > a[i]) {
            ans[i]++; tot--; mx = a[i];
        }
    }
    // for (int i = 1; i <= res; i++) dbg(dp[i]);
    // for (int i = 1; i <= n && tot <= res; i++) {
    //     if (dp[tot] == a[i]) {
    //         ans[i]++; tot++;
    //     }
    // }
    // for (int i = 1; i <= n; i++) {
    //     dbg(i, ans[i]);
    // }
}

int main() {
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    get(ans[0]); 
    // reverse(a + 1, a + 1 + n); get(ans[1]); 
    // for (int i = 1; i <= n; i++) {
        // dbg(i, ans[0][i], ans[1][i]);
    // }
    vector<int> v;
    for (int i = 1; i <= n; i++) if (!ans[0][i]) v.push_back(a[i]);
    for (int i = 1; i < v.size(); i++) if (v[i] >= v[i - 1]) return puts("NO"), 0;
    puts("YES");
    for (int i = 1; i <= n; i++) if (!ans[0][i]) printf("1 "); else printf("0 ");
    return 0;
}