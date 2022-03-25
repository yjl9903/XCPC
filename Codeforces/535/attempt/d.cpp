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
    cout << dp[n][0] << ' ' << dp[n][1] << ' ' << dp[n][2] << endl;
    for (int k = 0; k < 3; k++) {
        if (dp[n][k] != ans) continue;
        char last = p[k]; t[n] = p[k];
        int tot = ans;
        if (s[n] != last) tot--;
        for (int i = n - 1; i >= 1; i--) {
            if (s[i] == 'R') {
                if (dp[i][0] == tot && last != 'R') {
                    t[i] = 'R'; last = 'R';
                } else if (dp[i][1] + 1 == tot && last != 'G') {
                    tot--; t[i] = 'G'; last = 'G';
                } else {
                    tot--; t[i] = 'B'; last = 'B';
                }
            } else if (s[i] == 'G') {
                if (dp[i][0] + 1 == tot && last != 'R') {
                    tot--; t[i] = 'R';  last = 'R';
                } else if (dp[i][1] == tot && last != 'G') {
                    t[i] = 'G'; last = 'G';
                } else {
                    tot--; t[i] = 'B'; last = 'B';
                }
            } else {
                if (dp[i][0] + 1 == tot && last != 'R') {
                    tot--; t[i] = 'R';  last = 'R';
                } else if (dp[i][1] + 1 == tot && last != 'G') {
                    tot--; t[i] = 'G'; last = 'G';
                } else {
                    t[i] = 'B'; last = 'B';
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
        cout << t + 1 << endl;
    }
    printf("%d\n%s", ans, t + 1);
    return 0;
}