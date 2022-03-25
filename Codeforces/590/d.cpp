#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[maxn];
int n, q;

struct BIT {
    int a[maxn];
    void update(int i, int x) {
        for (; i <= n; i += i & -i) a[i] += x;
    }
    int query(int i) {
        int r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} f[26];

int main() {
    scanf("%s%d", s + 1, &q);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        f[s[i] - 'a'].update(i, 1);
    }
    int op, pos, l, r; char ch[3];
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%s", &pos, ch);
            f[s[pos] - 'a'].update(pos, -1);
            s[pos] = ch[0];
            f[s[pos] - 'a'].update(pos, 1);
        } else {
            scanf("%d%d", &l, &r);
            int ans = 0;
            for (int i = 0; i < 26; i++) {
                if (f[i].query(l, r)) ans++;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}