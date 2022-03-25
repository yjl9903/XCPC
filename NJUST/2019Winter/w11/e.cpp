#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int maxn = 5000 + 5;
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

// #define ENABLE_DOUBLE_HASH

// index start at 0
ull h1[maxn], h2[maxn];
ull Hash(char* s, ull* h) { 
    int length = strlen(s);
    ull res1 = 0, res2 = 0;
    h[length] = 0;  // ATTENTION!
    for (int j = length - 1; j >= 0; j--) {
    #ifdef ENABLE_DOUBLE_HASH
        res1 = (res1 * seed + s[j]) % p1;
        res2 = (res2 * seed + s[j]) % p2;
        h[j] = (res1 << 32) | res2;
    #else
        res1 = res1 * seed + s[j];
        h[j] = res1;
    #endif
    }
    return h[0];
}

// get hash of s[left...right-1]
ull get(ull* h, int left, int right) {
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

char s1[maxn], s2[maxn];

int main() {
    init();
    scanf("%s%s", s1, s2);
    Hash(s1, h1); Hash(s2, h2);
    int n = strlen(s1), m = strlen(s2);
    for (int len = 1; len <= min(n, m); len++) {
        // map<ull,int> mp1; 
        unordered_map<ull,int> mp1;
        unordered_map<ull,int> mp2;
        for (int i = 0; i + len <= n; i++) mp1[get(h1, i, i + len)]++;
        for (int i = 0; i + len <= m; i++) mp2[get(h2, i, i + len)]++;
        for (auto& x: mp1) {
            if (x.second != 1) continue;
            if (mp2[x.first] == 1) {
                printf("%d\n", len); return 0;
            }
        }
    }
    puts("-1");
    return 0;
}