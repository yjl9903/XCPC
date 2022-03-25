#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
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
const int mod = 998244353;
const int maxn = 5000 + 5;

int n, c[maxn], len;

char a[maxn];

int f[maxn][maxn];
int dp(int l, int r) {
    dbg(l, r);
    if (f[l][r] != -1) return f[l][r];
    if (l == r) return 1;
    if (l > r) return 0;
    
    if (a[l] == a[r]) {
        int last = l + 1, ans = 1;
        for (int i = l + 1; i <= r; i++) {
            if (a[i] == a[l]) {
                ans += dp(last, i - 1);
                last = i + 1;
            }
        }
        return f[l][r] = ans;
    }
    int ans1 = 1, last = l + 1;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] == a[l]) {
            ans1 += dp(last, i - 1);
            last = i + 1;
        }
    }
    ans1 += dp(last, r);
    int ans2 = 1; last = r - 1;
    for (int i = r - 1; i >= l; i--) {
        if (a[i] == a[r]) {
            ans2 += dp(i + 1, last);
            last = i - 1;
        }
    }
    ans2 += dp(l, last);
    return f[l][r] = min(ans1, ans2);
}

int main() {
    ms(f, -1);
    scanf("%d%s", &n, a + 1);
    cout << dp(1, n) << endl;
    return 0;
}