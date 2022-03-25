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
const int maxn = 600000 + 5;

int n, m, a[maxn];

struct Trie {
    static const int maxl = 25;
    int tot, ch[maxn * maxl][2], val[maxn * maxl], root[maxn];
    void clear() {
        tot = 0; ms(val, 0);
    }
    int node() {
        return ++tot;
    }
    void insert(int pre, int rt, int x) {
        pre = root[pre];
        rt = root[rt] = node();
        for (int i = maxl - 1; i >= 0; i--) {
            val[rt] = val[pre] + 1;
            int b = (x >> i) & 1;
            if (!ch[rt][b]) ch[rt][b] = node();
            ch[rt][b ^ 1] = ch[pre][b ^ 1];
            rt = ch[rt][b];
            pre = ch[pre][b];
        }
        val[rt] = val[pre] + 1;
    }
    int query(int pre, int rt, int x) {
        pre = root[pre]; rt = root[rt];
        int ans = 0;
        for (int i = maxl - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (val[ch[rt][b ^ 1]] - val[ch[pre][b ^ 1]]) {
                ans += 1 << i;
                rt = ch[rt][b ^ 1];
                pre = ch[pre][b ^ 1];
            } else {
                rt = ch[rt][b];
                pre = ch[pre][b];
            }
        }
        return ans;
    }
} f;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i); 
        a[i] ^= a[i - 1];
        f.insert(i - 1, i, a[i]);
    }
    char op[2]; int l, r, x;
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'A') {
            n++;
            scanf("%d", a + n);
            a[n] ^= a[n - 1];
            f.insert(n - 1, n, a[n]);
        } else {
            scanf("%d%d%d", &l, &r, &x);
            // important
            if (l == 1 && r == 1) printf("%d\n", a[n] ^ x);
            else printf("%d\n", f.query(max(0, l - 2), r - 1, a[n] ^ x));
        }
    }
    return 0;
}