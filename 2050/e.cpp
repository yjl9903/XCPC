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

int n, dp[maxn], mdp[maxn]; char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int n = strlen(s);
        for (int i = 0; i <= n; i++) dp[i] = 0, mdp[i] = 0;
        int mx = 0;
        for (int i = n - 1; i >= 0; i--) {
            int a = 0, b = 0, c = 0;
            for (int j = i; j < n; j++) {
                if (mdp[j] < mdp[i]) break;
                if (s[j] == 'A') a++;
                else if (s[j] == 'B') b++;
                else c++;
                int f = 0;
                if (c == 0) {
                    if (a >= 11 && a - b >= 2) {
                        dp[i] = max(dp[i], 1 + dp[j + 1]);
                        break;
                    } else if (b >= 11 && b - a >= 2) {
                        dp[i] = max(dp[i], 1 + dp[j + 1]);
                        break;
                    }
                } else {
                    if (a + c >= 11 && a + c - b >= 2) {
                        dp[i] = max(dp[i], 1 + dp[j + 1]);
                    } else if (b + c >= 11 && b + c - a >= 2) {
                        dp[i] = max(dp[i], 1 + dp[j + 1]);
                    } else {
                        int x = min(a, b), y = max(a, b), z = c;
                        if (z < y - x - 1) { 
                            x += c;
                            if (y >= 11 && y - x >= 2) {
                                dp[i] = max(dp[i], 1 + dp[j + 1]);
                                break;
                            }
                        } else {
                            // a += y - x + 1;
                            if (a < b) a += y - x + 1;
                            else b += y - x + 1;
                            c -= y - x + 1;
                            a += c / 2; b += c / 2;
                            c /= 2;
                            if (c) {
                                if (a < b) a++;
                                else b++;
                                c = 0;
                            }
                        }
                    }
                }
            }
            mdp[i] = max(mdp[i + 1], dp[i]);
        }
        printf("%d\n", dp[0]);
    }
    return 0;
}