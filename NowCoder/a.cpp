#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m;
char s[maxn];

namespace sam {
    int len[maxn], link[maxn], ch[maxn][26], tot, last;
    void init() {
        ms(ch, 0); tot = last = 1;
    }
    void insert(int c) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
    }
    ll cal(int m) {
        ll ans = 0;
        for (int i = 1; i <= tot; i++) {
            // ans += max(0, len[i] - len[link[i]] - m + 1);
            if (len[link[i]] + 1 >= m) ans += len[i] - len[link[i]];
            else {
                ans += max(len[i] - m + 1, 0);
            }
        }
        return ans;
    }
}

int main() {
    scanf("%d%d%s", &n, &m, s);
    sam::init();
    for (int i = 0; i < n; i++) sam::insert(s[i] - 'a');
    cout << sam::cal(m) << endl;
    return 0;
}