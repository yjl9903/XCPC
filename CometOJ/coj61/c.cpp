#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

char s[maxn], t[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s, t);
        int n = strlen(s), m = strlen(t);
        if (n != m + 2) {
            puts("0"); continue;
        }
        int st = 0, i = 0;
        for (i = 0; i < m; i++) {
            if (s[i] != t[i]) {
                st = i; break;
            }
        }
        for (; i < m && i + 1 < n; i++) {
            if (s[i + 1] != t[i]) {
                st = i + 1; break;
            }
        }
        for (; i < m && i + 2 < n; i++) {
            if (s[i + 2] != t[i]) {
                st = i + 2; break;
            }
        }
        if (i == m) puts("1");
        else puts("0");
    }
    return 0;
}