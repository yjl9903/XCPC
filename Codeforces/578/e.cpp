#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
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
const int seed = 135;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int p1 = 1e9 + 7, p2 = 1e9 + 9;
ull xp1[maxn], xp2[maxn];
void init() {
    mt19937 rnd(time(0));
    int prime[] = {
        (int)1e9 + 7, (int)1e9 + 9, 
        998244353, 91815541,
        122420729, 917120411,
        687840301, 515880193,
        1222827239, 1610612741
    };
    int x = rnd() % 10, y = rnd() % 10;
    while (x == y) y = rnd() % 10;
    p1 = prime[x], p2 = prime[y];

    xp1[0] = xp2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        xp1[i] = xp1[i - 1] * seed % p1;
        xp2[i] = xp2[i - 1] * seed % p2;
    }
}
ull h[maxn], h2[maxn];
ull get(int l, int r) {
    l--;
    int len = r - l;
    unsigned int mask32 = ~(0u);
    ull l1 = h[l] >> 32, r1 = h[r] >> 32;
    ull l2 = h[l] & mask32, r2 = h[r] & mask32;
    // dbg(l, r);
    // dbg(h[l], h[r]);
    // dbg(l1, r1, l2, r2);
    ull a = (r1 - l1 * xp1[len] % p1 + p1) % p1;
    ull b = (r2 - l2 * xp2[len] % p2 + p2) % p2;
    return (a << 32) | b;
}

int n, len;
char s[maxn], t[maxn];

int main() {
    init();
    scanf("%d%s", &n, s + 1);
    len = strlen(s + 1);
    ull res1 = 0, res2 = 0;
    for (int i = 1; i <= len; i++) {
        res1 = (res1 * seed + s[i]) % p1;
        res2 = (res2 * seed + s[i]) % p2;
        h[i] = (res1 << 32) | res2;
    }
    for (int i = 2; i <= n; i++) {
        scanf("%s", t + 1);
        int tlen = strlen(t + 1);
        ull r1 = 0, r2 = 0;
        int ans = 0;
        for (int j = 1; j <= tlen; j++) {
            r1 = (r1 * seed + t[j]) % p1;
            r2 = (r2 * seed + t[j]) % p2;
            ull tot = (r1 << 32) | r2;
            if (tot == get(len - j + 1, len)) ans = j;
        }
        for (int j = ans + 1; j <= tlen; j++) {
            s[++len] = t[j];
            res1 = (res1 * seed + s[len]) % p1;
            res2 = (res2 * seed + s[len]) % p2;
            h[len] = (res1 << 32) | res2;
        }
    }
    s[len + 1] = 0;
    printf("%s", s + 1);
    return 0;
}