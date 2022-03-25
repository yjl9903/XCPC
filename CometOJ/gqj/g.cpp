#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 200000 + 5;

namespace sam {
    int tot, last, cnt[maxn << 1], pos[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    int insert(int c, int i) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        pos[cur] = i;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                pos[nq] = pos[q];
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i >= 1; i--) {
            int u = a[i];
            pos[link[u]] = min(pos[link[u]], pos[u]);
        }
    }
}
using sam::pos;
using sam::ch;

int n, q;
char s[maxn];

int main() {
    sam::clear();
    scanf("%d%s", &q, s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        sam::insert(s[i] - 'a', i);
    }
    sam::rsort();
    while (q--) {
        scanf("%s", s + 1);
        int m = strlen(s + 1), u = 1, ans = n + 1;
        for (int i = 1; i <= m; i++) {
            int c = s[i] - 'a';
            for (int j = c + 1; j < 26; j++) {
                if (!ch[u][j]) continue;
                // dbg(i, j, ch[u][j], pos[ch[u][j]]);
                ans = min(ans, pos[ch[u][j]] - i + 1);
            }
            if (ch[u][c]) u = ch[u][c];
            else break;
        }
        if (ans + m - 1 <= n) printf("%d\n", ans - 1);
        else puts("-1");
    }
    return 0;
}