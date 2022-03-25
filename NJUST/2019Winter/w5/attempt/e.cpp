#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ull,ull> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;
const int seed = 135;
const int p1 = 1e9 + 7;
const int p2 = 1e9 + 9;

char s[maxn]; int n, q;

ull h[26][maxn], hh[26][maxn], xp[maxn] = {1}, xpp[maxn] = {1};
void Hash(){
    for (int c = 0; c < 26; c++) {
        ull ans = 0; h[c][n] = hh[c][n] = 0;
        for (int i = n - 1; i >= 0; i--) ans = (ans * seed + (s[i] - 'a' == c ? 1 : 0)) % p1, h[c][i] = ans;
        ans = 0;
        for (int i = n - 1; i >= 0; i--) ans = (ans * seed + (s[i] - 'a' == c ? 1 : 0)) % p2, hh[c][i] = ans;
    }
}
ull cal(int i, int l, int r) {
    int len = r - l;
    return (h[i][l] - h[i][r] * xp[len] % p1 + p1) % p1; 
}
ull cal2(int i, int l, int r) {
    int len = r - l;
    return (hh[i][l] - hh[i][r] * xpp[len] % p2 + p2) % p2; 
}

int main(){
    for (int i = 1; i < maxn; i++) xp[i] = xp[i - 1] * seed % p1;
    for (int i = 1; i < maxn; i++) xpp[i] = xpp[i - 1] * seed % p2;
    scanf("%d%d%s", &n, &q, s);
    Hash(); int x, y, len;
    while (q--) {
        scanf("%d%d%d", &x, &y, &len);
        vector<PII> va, vb;
        for (int c = 0; c < 26; c++) {
            va.push_back({cal(c, x, x + len), cal2(c, x, x + len)});
            vb.push_back({cal(c, y, y + len), cal2(c, y, y + len)});
        }
        sort(va.begin(), va.end());
        sort(vb.begin(), vb.end());
        int flag = 0;
        for (int i = 0; i < 26; i++) if (va[i] != vb[i]) { flag = 1; break; }
        if (flag) puts("NO");
        else puts("YES");
    }
    return 0;
}