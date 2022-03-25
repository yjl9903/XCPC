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
const int maxn = 200000 + 5;

int n, ans[maxn];
char d[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, d + 1);
        for (int i = 1; i <= n; i++) ans[i] = 2;
        int ok = 0;
        for (int c = 0; c <= 9 && ok == 0; c++) {
            vector<int> vis(n + 1, 0);
            int flag = 1, lp1 = 1, lp2 = n;
            char last1 = '0', last2 = '0';
            for (int i = 1; i <= n; i++) {
                if (d[i] < c + '0') {
                    vis[i] = 1;
                    if (d[i] < last1) {
                        flag = 0; break;
                    }
                    last1 = d[i];
                    lp1 = i;
                } else if (d[i] > c + '0') {
                    vis[i] = 2;
                    if (d[i] < last2) {
                        flag = 0; break;
                    }
                    last2 = d[i];
                    if (lp2 == n) lp2 = i;
                }
            }
            if (!flag) continue;
            for (int i = lp1; i <= n; i++) {
                if (d[i] == c + '0') {
                    vis[i] = 1;
                }
            }
            for (int i = lp2; i >= 1; i--) {
                if (d[i] == c + '0') {
                    vis[i] = 2;
                }
            }
            for (int i = 1; i <= n; i++) if (!vis[i]) {
                flag = 0; break;
            }
            if (!flag) continue;
            ok = 1;
            for (int i = 1; i <= n; i++) ans[i] = vis[i];
        }
        if (ok) {
            for (int i = 1; i <= n; i++) putchar(ans[i] + '0');
            puts("");
        } else {
            puts("-");
        }
    }
    return 0;
}