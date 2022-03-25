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
const int mod = 1000000007;
const int maxn = 1000000 + 5;

char s[maxn], t[maxn];

int nxt[maxn], cnt[maxn], n, m;
void getnxt(char *p){
    int len = strlen(p), k = -1, i = 0; nxt[0] = -1;
    while (i < len){
        if (k == -1 || p[k] == p[i]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
}
void kmp() {
    getnxt(t);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || s[i] == t[j]) {
            i++; j++;
        } else j = nxt[j];
        cnt[j]++;
        if (j >= m) j = nxt[j];
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        ms(cnt, 0);
        scanf("%s%s", s, t);
        n = strlen(s), m = strlen(t);
        reverse(s, s + n); reverse(t, t + m);
        kmp();
        for (int i = m; i > 0; i--) cnt[nxt[i]] += cnt[i];
        // for (int i = 1; i <= m; i++) dbg(i + 1, cnt[i]);
        ll ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += 1ll * i * cnt[i] % mod; if (ans >= mod) ans -= mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}