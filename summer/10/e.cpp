#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 100000 + 5;

PII eq[50];

int ans, cnt[20], suf[50];
void dfs(int now, int w) {
    ans = max(ans, w);
    if (w + suf[now] < ans) return ;
    if (now == 21) return ;
    int a = eq[now].first, b = eq[now].second;
    if (a == b) {
        if (cnt[a] >= 2 && cnt[a + b] >= 1) {
            cnt[a] -= 2; cnt[a + b]--;
            dfs(now + 1, w + 1);
            cnt[a] += 2; cnt[a + b]++;
        }
    } else {
        if (cnt[a] >= 1 && cnt[b] >= 1 && cnt[a + b] >= 1) {
            cnt[a]--; cnt[b]--; cnt[a + b]--;
            dfs(now + 1, w + 1);
            cnt[a]++; cnt[b]++; cnt[a + b]++;
        }
        if (cnt[a] >= 2 && cnt[b] >= 2 && cnt[a + b] >= 2) {
            cnt[a] -= 2; cnt[b] -= 2; cnt[a + b] -= 2;
            dfs(now + 1, w + 2);
            cnt[a] += 2; cnt[b] += 2; cnt[a + b] += 2;
        }
    }
    dfs(now + 1, w);
}

int main() {
    int c = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = i; i + j <= 9; j++) {
            eq[++c] = {i, j};
        }
    }
    for (int i = c; i >= 1; i--) {
        suf[i] = suf[i + 1] + 2;
        if (eq[i].first == eq[i].second) suf[i]--;
    }
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        for (int i = 1; i <= 9; i++) scanf("%d", cnt + i);
        ans = 0;
        dfs(1, 0);
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}