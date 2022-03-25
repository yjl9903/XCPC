#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

char p[5] = "RGB";
int n, dp[maxn][3]; char s[maxn], t[maxn];

int main(){
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);
        if (s[i] == 'R') {
            dp[i][1]++; dp[i][2]++;
        } else if (s[i] == 'G') {
            dp[i][0]++; dp[i][2]++;
        } else {
            dp[i][0]++; dp[i][1]++;
        } 
        dbg(dp[i][0], dp[i][1], dp[i][2]);
    }
    int ans = min(min(dp[n][0], dp[n][1]), dp[n][2]);
    for (int k = 0; k < 3; k++) {
        if (dp[n][k] != ans) continue;
        char last = p[k]; 
        t[n] = p[k];

        for (int i = n - 1; i >= 1; i--) {
            if (t[i + 1] == 'R') {
                dbg(dp[i + 1][0], dp[i][1], dp[i][2], s[i]);
                if (dp[i][1] + (s[i + 1] == 'R' ? 0 : 1) == dp[i + 1][0]) t[i] = 'G';
                else if (dp[i][2] + (s[i + 1] == 'R' ? 0 : 1) == dp[i + 1][0]) t[i] = 'B';
                else {
                    // cout << "???\n";
                }
            } else if (t[i + 1] == 'G') {
                dbg(dp[i + 1][1], dp[i][0], dp[i][2], s[i]);
                if (dp[i][0] + (s[i + 1] == 'G' ? 0 : 1) == dp[i + 1][1]) t[i] = 'R';
                else if (dp[i][2] + (s[i + 1] == 'G' ? 0 : 1) == dp[i + 1][1]) t[i] = 'B';
                else {
                    // cout << "???\n";
                }
            } else {
                dbg(dp[i + 1][2], dp[i][0], dp[i][1], s[i]);
                if (dp[i][0] + (s[i + 1] == 'B' ? 0 : 1) == dp[i + 1][2]) t[i] = 'R';
                else if (dp[i][1] + (s[i + 1] == 'B' ? 0 : 1) == dp[i + 1][2]) t[i] = 'G';
                else {
                    // cout << "???\n";
                }
            }
        }

        int flag = 1;
        for (int i = 1; i < n; i++) {
            if (t[i - 1] == t[i]) {
                flag = 0; break;
            }
        }
        if (flag) break;
        // cout << t + 1 << endl;
    }
    printf("%d\n%s", ans, t + 1);
    return 0;
}