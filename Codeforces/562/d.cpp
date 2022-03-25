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
const int maxn = 300000 + 5;

char s[maxn];
int n;

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    ll ans = 1ll * (n + 1) * n / 2;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int f = 0;
            for (int k = 1; j - 2 * k >= i; k++) {
                if (s[j - 2 * k] == s[j - k] && s[j - k] == s[j]) {
                    dbg(s[j - 2 * k], s[j - k], s[j]);
                    f = 1; break;
                }
            }
            if (f) break;
            ans--;
        }
    }
    cout << ans;
    return 0;
}