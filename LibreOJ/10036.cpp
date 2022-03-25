#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int maxn = 500000 + 5;
const int seed = 135;
const int p1 = 1e9 + 7, p2 = 1e9 + 9;

ull xp1[maxn], xp2[maxn], xp[maxn];
void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        xp1[i] = xp1[i - 1] * seed % p1;
        xp2[i] = xp2[i - 1] * seed % p2;
        xp[i] = xp[i - 1] * seed;
    }
}

#define ENABLE_DOUBLE_HASH

// index start at 0
ull h[maxn], hl[maxn];
ull Hash(char* s) { 
    int length = strlen(s);
    ull res1 = 0, res2 = 0;
    h[length] = 0;  // ATTENTION!
    for (int j = length - 1; j >= 0; j--) {
    #ifdef ENABLE_DOUBLE_HASH
        res1 = (res1 * seed + s[j]) % p1;
        res2 = (res2 * seed + s[j]) % p2;
        h[j] = (res1 << 32) | res2;
    #else
        res1 = res1 * x + s[j];
        h[j] = res1;
    #endif
    }
    return h[0];
}

// get hash of s[left...right)
ull get(int left, int right) {
    int len = right - left;
#ifdef ENABLE_DOUBLE_HASH
    unsigned int mask32 = ~(0u);
    ull left1 = h[left] >> 32, right1 = h[right] >> 32;
    ull left2 = h[left] & mask32, right2 = h[right] & mask32;
    return (((left1 - right1 * xp1[len] % p1 + p1) % p1) << 32) |
           (((left2 - right2 * xp2[len] % p2 + p2) % p2));
#else
    return h[left] - h[right] * xp[len];
#endif
}

int n; char s[maxn];

int main() {
    init();
    while (scanf("%s", s) == 1) {
        n = strlen(s); Hash(s);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (get(0, i + 1) == get(n - i - 1, n)) ans.push_back(i);
        }
        for (int i = 0; i < ans.size(); i++) {
            if (i) putchar(' ');
            printf("%d", ans[i] + 1);
        }
        puts("");
    }
    return 0;
}