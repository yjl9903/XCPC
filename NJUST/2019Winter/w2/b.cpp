#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
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
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, k, dp[maxn][2];
char s[2][maxn];
int flag = 0;

// void dfs(int p, int k, int t) {
//     dbg(k, p, t);
//     if (p >= n || p + ::k > n) {
//         flag = 1; return;
//     }
//     if (t >= p) return;
//     if (dp[p][k] != -1 && dp[p][k] <= t) return;
//     dp[p][k] = t;
//     if (p > 1 && s[k][p - 1] == '-') dfs(p - 1, k, t + 1);
//     if (s[k][p + 1] == '-') dfs(p + 1, k, t + 1);
//     if (s[k ^ 1][p + ::k] == '-') dfs(p + ::k, k ^ 1, t + 1);
// }

struct node {
    int k, p, t;
};

int bfs() {
    queue<node> q; q.push({0, 1, 0});
    while (!q.empty()) {
        node x = q.front(); q.pop();
        dbg(x.k, x.p, x.t);
        if (x.p + k > n) return 1;
        if (x.t >= x.p) continue;
        if (dp[x.p][x.k] != -1 && dp[x.p][x.k] <= x.t) continue;
        dp[x.p][x.k] = x.t;
        if (x.p > 1 && s[x.k][x.p - 1] == '-' && x.t + 1 < x.p - 1) {
            q.push({x.k, x.p - 1, x.t + 1});
        }
        if (s[x.k][x.p + 1] == '-' && x.t + 1 < x.p + 1) {
            q.push({x.k, x.p + 1, x.t + 1});
        }
        if (s[x.k ^ 1][x.p + k] == '-' && x.t + 1 < x.p + k) {
            q.push({x.k ^ 1, x.p + k, x.t + 1});
        }
    }
    return 0;
}

int main(){
    scanf("%d%d%s%s", &n, &k, s[0] + 1, s[1] + 1);
    for (int i = n + 1; i < maxn; i++) s[0][i] = s[1][i] = '-';
    ms(dp, -1);
    // dp[1][0] = 0;
    if (bfs()) puts("YES");
    else puts("NO");
    return 0;
}