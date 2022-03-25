#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <deque>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000000 + 5;

int n, k; char s[maxn];

// int dp[maxn][21];
// void init(){
//   for (int i = 1; i <= n; i++) dp[i][0] = i;
//   for (int j = 1; j < 21; j++)
//     for (int i = 1; i + (1 << j) <= n + 1; i++) {
//       if (s[dp[i][j - 1]] <= s[dp[i + (1 << (j - 1))][j - 1]]) 
//         dp[i][j] = dp[i][j - 1];
//       else 
//         dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
//     }
// }
// int rmq(int l, int r){
//   int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
//   if (s[dp[l][k]] <= s[dp[r - (1 << k) + 1][k]]) return dp[l][k];
//   else return dp[r - (1 << k) + 1][k];
// }

int main() {
  scanf("%s%d", s + 1, &k);
  n = strlen(s + 1);
  // init();
  int last = 1;
  string ans;
  // vector<int> stk;
  deque<int> stk;
  for (int i = 0; i < k; i++) {
    // int x = rmq(last, n - k + i + 1);
    // ans += s[x]; last = x + 1;
    while (last <= n - k + i + 1) {
      while (!stk.empty() && s[stk.back()] > s[last]) {
        stk.pop_back();
      }
      stk.push_back(last); last++;
    }
    ans += s[stk.front()]; stk.pop_front();
  }
  cout << ans;
  return 0;
}