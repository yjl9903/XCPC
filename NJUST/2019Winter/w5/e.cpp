#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int seed = 135;
const int maxn = 1000000 + 10;
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
char s[maxn];
ull h[26][maxn], hl[maxn];
ull Hash() { 
    int length = strlen(s);
    for (int c = 0; c < 26; c++) {
        ull res1 = 0, res2 = 0;
        h[c][length] = 0;  // ATTENTION!
        for (int j = length - 1; j >= 0; j--) {
        #ifdef ENABLE_DOUBLE_HASH
            res1 = (res1 * seed + (s[j] - 'a' == c)) % p1;
            res2 = (res2 * seed + (s[j] - 'a' == c)) % p2;
            h[c][j] = (res1 << 32) | res2;
        #else
            res1 = res1 * x + s[j];
            h[j] = res1;
        #endif
        }
    }
    return h[0][0];
}

// 获取子串哈希，左闭右开区间
ull get(int c, int left, int right) {
    int len = right - left;
#ifdef ENABLE_DOUBLE_HASH
    // get hash of s[left...right-1]
    unsigned int mask32 = ~(0u);
    ull left1 = h[c][left] >> 32, right1 = h[c][right] >> 32;
    ull left2 = h[c][left] & mask32, right2 = h[c][right] & mask32;
    return (((left1 - right1 * xp1[len] % p1 + p1) % p1) << 32) |
            (((left2 - right2 * xp2[len] % p2 + p2) % p2));
#else
    return h[left] - h[right] * xp[len];
#endif
}

int n, q;

int main(){
    init();
    scanf("%d%d%s", &n, &q, s);
    Hash(); int x, y, len;
    while (q--) {
        scanf("%d%d%d", &x, &y, &len);
        x--; y--;
        vector<ull> va, vb;
        for (int c = 0; c < 26; c++) {
            va.push_back(get(c, x, x + len));
            vb.push_back(get(c, y, y + len));
        }
        sort(va.begin(), va.end());
        sort(vb.begin(), vb.end());
        if (va == vb) puts("YES");
        else puts("NO");
    }
    return 0;
}