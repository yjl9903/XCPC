#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn]; char s[maxn];
ll dp[maxn][5], ct[maxn][5];

int main(){
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i][j] = dp[i - 1][j];
        }
        if (s[i] == 'h') { // y
            dp[i][0] += 1ll * a[i]; 
        } else if (s[i] == 'a') { 
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + a[i]); 
        } else if (s[i] == 'r') { 
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][2] + a[i]);
        } else if (s[i] == 'd') {
            dp[i][3] = min(dp[i - 1][2], dp[i - 1][3] + a[i]);
        }
        dbg(dp[i][0], dp[i][1], dp[i][2], dp[i][3]);
    }
    cout << dp[n][3];
    return 0;
}