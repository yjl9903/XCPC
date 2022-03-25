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
const int maxn = 100000 + 5;

char s[maxn], t[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s, t);
        int slen = strlen(s), tlen = strlen(t);
        reverse(s, s + slen); reverse(t, t + tlen);
        int pos, ans = 0;
        for (int i = 0; i < tlen; i++) if (t[i] == '1') {
            pos = i; break;
        }
        for (int i = pos; i < slen; i++) {
            if (s[i] == '1') {
                ans = i - pos; break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}