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

char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int ans = 0;
        for (int i = 0; i < 4; i++) {
            scanf("%s", s);
            if (s[2] == 'T') ans = (s[0] - 'A') + 1;
        }
        putchar(ans + '0');
    }
    return 0;
}