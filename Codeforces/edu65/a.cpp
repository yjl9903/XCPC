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

int n; char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s + 1);
        int pos = -1;
        for (int i = 1; i <= n; i++) if (s[i] == '8') {
            pos = i; break;
        }
        if (pos == -1) puts("NO");
        else {
            if (n - pos >= 10) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}