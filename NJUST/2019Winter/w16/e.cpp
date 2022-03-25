#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;
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
        res1 = res1 * seed + s[j];
        h[j] = res1;
    #endif
    }
    return h[0];
}

// get hash of s[left...right-1]
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

int n, m, y[maxn]; char s[maxn];



int main() {
    init();
    scanf("%d%d%s", &n, &m, s);
    int len = strlen(s); Hash(s);
    if (m == 0) {
        ll ans = 1; 
        for (int i = 1; i <= n; i++) ans = ans * 26ll % mod;
        cout << ans << endl;
        return 0;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", y + i); y[i]--;
    }
    int cnt = len, flag = 0;
    for (int i = 1; i < m; i++) {
        if (y[i - 1] + len - 1 >= y[i]) {
            cnt += y[i] - y[i - 1];
            // cout << y[i - 1] + len - y[i] << ' ' << y[i] - y[i - 1] << endl;
            if (get(0, y[i - 1] + len - y[i]) != get(y[i] - y[i - 1], len)) 
                flag = 1;
        } else {
            cnt += len;
        }
    }
    if (flag) puts("0");
    else {
        // cout << cnt << endl;
        ll ans = 1; 
        for (int i = 1; i <= n - cnt; i++) ans = ans * 26ll % mod;
        cout << ans << endl;
    }
    return 0;
}