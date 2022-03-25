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

namespace manacher {
    char s[maxn << 1] = "##";
    int n, hw[maxn << 1];
    void manacher() {
        int maxr = 0, m = 0;
        for (int i = 1; i < n; i++) {
            if (i < maxr) hw[i] = min(hw[m * 2 - i], hw[m] + m - i);
            else hw[i] = 1;
            while (s[i + hw[i]] == s[i - hw[i]]) hw[i]++;
            if (hw[i] + i > maxr) {
                m = i; maxr = hw[i] + i;
            }
        }
    }
    void build(char a[]) {
        int i;
        for (i = 1; a[i]; i++) {
            s[i * 2] = a[i];
            s[i * 2 + 1] = '#';
        }
        n = i * 2; s[n] = 0;
        manacher();
    }
    void get(int tag[]) {
        for (int i = 1; i < n; i++) {
            int l = i / 2 + i % 2;
            int r = l + hw[i] / 2 - 1;
            if (l <= r) tag[l]++, tag[r + 1]--;
        }
    }
}

namespace exkmp {
    int nxt[maxn], extend[maxn];
    void getnxt(int n, char *s) {
        int p = 1, k = 2; nxt[1] = n;
        while (p + 1 <= n && s[p] == s[p + 1]) p++;
        nxt[2] = p - 1;
        for (int i = 3; i <= n; i++) {
            int len = nxt[i - k + 1];
            if (len + i <= p) nxt[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= n && s[j + 1] == s[i + j]) j++;
                nxt[i] = j; k = i;
                p = i + j - 1;
            }
        }
    }
    void build(int tlen, char *t, int slen, char *s) { 
        getnxt(slen, s); 
        int p = 1, k = 1;
        while (p <= tlen && p <= slen && t[p] == s[p]) p++;
        p--; extend[1] = p;
        for (int i = 2; i <= tlen; i++) {
            int len = nxt[i - k + 1];
            if (len + i <= p) extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= tlen && j <= slen && s[j + 1] == t[i + j]) j++;
                extend[i] = j; k = i;
                p = i + j - 1;
            }
        }
    }
}
using exkmp::extend;

char s[maxn], t[maxn];
int slen, tlen, pad[maxn];

int main() {
    scanf("%s%s", s + 1, t + 1);
    slen = strlen(s + 1);
    tlen = strlen(t + 1);
    reverse(s + 1, s + slen + 1);
    exkmp::build(slen, s, tlen, t);
    manacher::build(s);
    manacher::get(pad);
    for (int i = 1; i <= slen; i++) pad[i] += pad[i - 1];
    ll ans = 0;
    for (int i = 2; i <= slen; i++) {
        ans += 1ll * pad[i - 1] * extend[i];
    }
    cout << ans;
    return 0;
}