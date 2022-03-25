#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
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
const int maxn = 300000 + 5;

int n, val[maxn], pre[maxn], suf[maxn];
char s[maxn];
int le[maxn], ri[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        val[i] = val[i - 1];
        if (s[i] == '(') val[i]++;
        else val[i]--;
    }
    if (val[n]) return puts("0\n1 1"), 0;
    int mn = 0, shift = 0;
    for (int i = 1; i <= n; i++) mn = min(val[i], mn);
    for (int i = 1; i <= n; i++) {
        if (val[i] == mn) {
            shift = i;
            string str(s + 1);
            str = str.substr(i) + str.substr(0, i + 1);
            for (int i = 1; i <= n; i++) s[i] = str[i - 1];
            break;
        }
    }
    auto srcpos = [&](int x) {
        return (x - 1 + shift) % n + 1;
    };
    for (int i = 1; i <= n; i++) {
        val[i] = val[i - 1];
        if (s[i] == '(') val[i]++;
        else val[i]--;
    }
    vector<int> ans = {0, 1, 1};
    int all = 0;
    for (int i = 1; i <= n; i++) if (val[i] == 0) all++;
    int cnt = 0, last = 0;
    // dbg(s + 1);
    for (int i = 1; i <= n; i++) {
        if (val[i] == 2) cnt++;
        else if (val[i] <= 1) {
            // dbg(i, last + 1, all + cnt);
            ans = max(ans, (vector<int>){ all + cnt, srcpos(last + 1), srcpos(i) });
            cnt = 0; last = i;
        }
    }
    cnt = 0; last = 0;
    for (int i = 1; i <= n; i++) {
        if (val[i] == 1) cnt++;
        else if (val[i] == 0) {
            ans = max(ans, (vector<int>{cnt, srcpos(last + 1), srcpos(i) }));
            cnt = 0; last = i;
        }
    }
    printf("%d\n%d %d", ans[0], ans[1], ans[2]);
    return 0;
}