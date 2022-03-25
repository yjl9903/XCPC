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
const int maxn = 1000000 + 5;

char s[maxn], ans[maxn];
int n, pre[maxn], cnt[maxn];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i - 1];
        if (s[i] == '(') pre[i] = pre[i - 1] + 1, cnt[i]++;
        else pre[i] = pre[i - 1] - 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        if (s[i] == ')' && s[i + 1] == '(') {
            for (int j = 1; j < i; j++) ans[j] = s[j];
            ans[i] = '('; ans[i + 1] = ')';

            int c1 = cnt[i + 1], c2 = i + 1 - cnt[i + 1], p = pre[i + 1];
            dbg(i + 1, c1, c2, p);
            for (int j = i + 2; j <= n; j++) {
                if (p > 0 && c2 < n / 2) ans[j] = ')', p--, c2++;
                else ans[j] = '(', p++, c1++;
            }
            puts(ans + 1);

            break;
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        if (s[i] == '(' && s[i + 1] == ')') {
            if (pre[i] == 1) continue;
            for (int j = 1; j < i; j++) ans[j] = s[j];
            ans[i] = ')'; ans[i + 1] = '(';

            int c1 = cnt[i + 1], c2 = i + 1 - cnt[i + 1];
            for (int j = i + 2; j <= n; j++) {
                if (c1 < n / 2) ans[j] = '(', c1++;
                else ans[j] = ')';
            }
            puts(ans + 1);
            
            break;
        }
    }
    return 0;
}