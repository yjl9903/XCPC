#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 3e6 + 17;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int maxq = 20000 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0; 
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}
inline void gs(char* s) {
    int pos = 1;
    char c = buff.get();
    while (c < 'a' || c > 'z') c = buff.get();
    while (c >= 'a' && c <= 'z') s[pos++] = c, c = buff.get();
    s[pos] = 0;
}

char s[maxn], tmp[maxn];
int n, q, ans[maxq];
string qs[maxq];
vector<int> bag[maxn];

vector<int> get(const string& s) {
    vector<int> v(28, 0);
    int l = (int)s.length();
    for (int i = 1; i + 1 < l; i++) {
        v[s[i] - 'a']++;
    }
    v[26] = s[0] - 'a';
    v[27] = s[l - 1] - 'a';
    return v;
}

int prime_table[] = {3793,21347,56569,56813,84859,123433,129403,159667,270563,298513,354143,422761,450083,458407,465989,514751,609619,659999,758633,769243,775241,803237,804757,846913,864167,897349,908129,966419};
ull getHash(const vector<int>& v) {
    assert((int)v.size() == 28);
    ull res = 0;
    for (int i = 0; i < 28; i++) {
        res += prime_table[i] * v[i];
    }
    return res;
}

int mp[mod];

int main() {
    int T = gi();
    while (T--) {
        gs(s); q = gi();
        n = strlen(s + 1);
        for (int i = 1; i <= q; i++) {
            gs(tmp);
            int l = strlen(tmp + 1);
            qs[i] = string(tmp + 1);
            if (l <= n) {
                bag[l].push_back(i);
            }
            ans[i] = 0;
        }
        for (int len = 2; len <= n; len++) {
            if (bag[len].empty()) continue;
            vector<int> info(28, 0);
            info[26] = s[1] - 'a';
            info[27] = s[len] - 'a';
            for (int i = 2; i < len; i++) {
                info[s[i] - 'a']++;
            }
            vector<ull> cl;
            ull res = getHash(info);
            mp[res % mod]++;
            cl.push_back(res % mod);
            for (int i = 2; i + len - 1 <= n; i++) {
                info[s[i] - 'a']--;
                res -= prime_table[s[i] - 'a'];
                res -= info[26] * prime_table[26];
                info[26] = s[i] - 'a';
                res += info[26] * prime_table[26];
                info[info[27]]++;
                res += prime_table[info[27]];
                res -= info[27] * prime_table[27];
                info[27] = s[i + len - 1] - 'a';
                res += info[27] * prime_table[27];
                
                mp[res % mod]++;
                cl.push_back(res % mod);
            }
            for (auto& q: bag[len]) {
                ull x = getHash(get(qs[q]));
                ans[q] = mp[x % mod];
            }
            for (ull x: cl) mp[x] = 0;
        }
        for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
        for (int i = 1; i <= n; i++) bag[i].clear();
        for (int i = 1; i <= q; i++) qs[i].clear();
    }
    return 0;
}