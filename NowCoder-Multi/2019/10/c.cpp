#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 20;

const int p1 = 1e9 + 7, p2 = 1e9 + 9;
const int seed = 135;
ull xp1[maxn], xp2[maxn], xp[maxn], h[maxn];
void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        xp1[i] = xp1[i - 1] * seed % p1;
        xp2[i] = xp2[i - 1] * seed % p2;
        xp[i] = xp[i - 1] * seed;
    }
}

char t[10], op[10];
int n, s[maxn], le[maxn], ri[maxn], ans[maxn];

int get(const char* s) {
    if (s[0] == 'd') return 1;
    if (s[0] == 'r') return 2;
    if (s[0] == 'm') return 3;
    if (s[0] == 'f') return 4;
    if (s[0] == 's' && s[1] == 'o') return 5;
    if (s[0] == 'l') return 6;
    if (s[0] == 's' && s[1] == 'i') return 7;
    return 0;
}

int main() {
    init();
    scanf("%d", &n);
    int tl = 1000000 + 5, tr = tl - 1;
    for (int i = 1; i <= n; i++) {
        scanf("%s%s", op, t);
        if (op[0] == 'a') {
            s[++tr] = get(t);
        } else {
            s[--tl] = get(t);
        }
        le[i] = tl;
    }
    ull res1 = 0, res2 = 0;
    for (int i = tl; i <= tr; i++) {
        res1 = (res1 * seed + s[i]) % p1;
        res2 = (res2 * seed + s[i]) % p2;
        h[i] = (res1 << 32) | res2;
    }
    auto get = [&](int l, int r) {
        l--; int len = r - l;
        unsigned int mask32 = ~(0u);
        ull l1 = h[l] >> 32, r1 = h[r] >> 32;
        ull l2 = h[l] & mask32, r2 = h[r] & mask32;
        ull a = (r1 - l1 * xp1[len] % p1 + p1) % p1;
        ull b = (r2 - l2 * xp2[len] % p2 + p2) % p2;
        return (a << 32) | b;
    };
    for (int i = 1; i <= n; i++) {
        int l = i, r = n, pos = i;
        while (l <= r) {
            int m = (l + r) / 2;
            if (get(le[m], le[m] + m - i - 1) == get(le[m] + i, le[m] + m - 1))
                pos = m, l = m + 1;
            else r = m - 1;
        }
        ans[i]++; ans[pos + 1]--;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        printf("%d\n", ans[i]);
    }
    return 0;
}