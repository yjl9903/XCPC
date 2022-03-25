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
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000 + 5;

int nxt[maxn];
void getfail(int len, char* s, int fail[]) {
    fail[1] = 0;
    for (int i = 2; i <= len; i++) {
        int cur = fail[i - 1];
        while (cur > 0 && s[cur + 1] != s[i])
            cur = fail[cur];
        if (s[cur + 1] == s[i])
            ++cur;
        fail[i] = cur;
    }
}
bool kmp(char *s, char *p) {
    int slen = strlen(s + 1), plen = strlen(p + 1), cur = 0;
    getfail(plen, p, nxt);
    for (int i = 1; i <= slen; i++) {
        while (cur > 0 && s[i] != p[cur + 1]) cur = nxt[cur];
        if (p[cur + 1] == s[i]) cur++;
        if (cur == plen) {
            return true;
        }
    }
    return false;
}

char s[505][maxn];
int n, len[505], ok[505];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> opt;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i] + 1);
            len[i] = strlen(s[i] + 1);
            if (i > 1) {
                ok[i] = kmp(s[i], s[i - 1]);
                if (!ok[i]) opt.push_back(i - 1);
            }
        }
        // dbg("---");
        // for (int i = 1; i <= n; i++) dbg(ok[i]);
        int ans = -1;
        for (int i = n; i >= 1; i--) {
            int flag = 0;
            for (int x: opt) {
                if (x >= i) break;
                if (!kmp(s[i], s[x])) {
                    flag = 1; break;
                }
            }
            if (flag) {
                ans = i; break;
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}