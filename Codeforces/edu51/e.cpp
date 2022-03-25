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

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
int c[maxn];
void update(int i, int x) {
    for (i++; i < maxn; i += i & -i) c[i] = add(c[i], x);
}
int query(int i) {
    if (i < 0) return 1;
    int r = 0;
    for (i++; i; i -= i & -i) r = add(r, c[i]);
    return r;
}
void update(int l, int r, int x) {
    update(l, x); update(r + 1, mod - x);
}

char a[maxn], l[maxn], r[maxn];
int alen, llen, rlen;

int nxt1[maxn], extend1[maxn], nxt2[maxn], extend2[maxn];
void getnxt(char *s, int* nxt){
    int n = strlen(s), p = 0, k = 1; nxt[0] = n;
    while (p + 1 < n && s[p] == s[p + 1]) p++;
    nxt[1] = p;
    for (int i = 2; i < n; i++){
        p = k + nxt[k] - 1;
        if (i + nxt[i - k] <= p) nxt[i] = nxt[i - k];
        else {
            int j = max(p - i + 1, 0);
            while (i + j < n && s[i + j] == s[j]) j++;
            nxt[i] = j; k = i;
        }
    }
}
void exkmp(char *t, char *s, int *nxt, int *extend){ 
    getnxt(s, nxt); 
    int tlen = strlen(t), slen = strlen(s), p = 0, k = 0;
    while (p < tlen && p < slen && t[p] == s[p]) p++;
    extend[0] = p;
    for (int i = 1; i < tlen; i++){
        p = k + extend[k] - 1;
        if (i + nxt[i - k] <= p) extend[i] = nxt[i - k];
        else {
            int j = max(p - i + 1, 0);
            while (i + j < tlen && j < slen && t[i + j] == s[j]) j++;
            extend[i] = j; k = i;
        }
    }
}

int check1(int x, int y) {
    if (y - x + 1 < llen) return 0;
    int len = extend1[x];
    if (len >= y - x + 1) return 1;
    return a[x + len] > l[len];
}
int check2(int x, int y) {
    if (y - x + 1 < rlen) return 1;
    int len = extend2[x];
    if (len >= y - x + 1) return 1;
    return a[x + len] < r[len];
}

int dp[maxn];

int main() {
    scanf("%s%s%s", a, l, r);
    exkmp(a, l, nxt1, extend1);
    exkmp(a, r, nxt2, extend2);
    alen = strlen(a);
    llen = strlen(l);
    rlen = strlen(r);
    for (int i = 0; i < alen; i++) {
        int x, y;
        if (a[i] == '0') {
            if (l[0] == '0') {
                update(i, i, query(i - 1));
            }
            continue;
        }
        x = min(i + llen - 1, alen - 1);
        y = min(i + rlen - 1, alen - 1);
        if (!check1(i, x)) x++;
        if (!check2(i, y)) y--;
        if (x <= y) update(x, y, query(i - 1));
    }
    cout << query(alen - 1);
    return 0;
}