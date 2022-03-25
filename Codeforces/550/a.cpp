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
        cin >> s;
        int n = strlen(s), flag = 1;
        sort(s, s + n);
        for (int i = 1; i < n; i++) {
            if (s[i - 1] + 1 != s[i]) {
                flag = 0; break;
            }
        }
        if (flag) puts("YES");
        else puts("NO");
    }
    return 0;
}