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
        scanf("%s", s);
        int n = strlen(s);
        if (n % 4) puts("No");
        else {
            int flag = 1;
            for (int i = 0; i < n; i += 4) {
                if (s[i] == '2' && s[i + 1] == '0' && s[i + 2] == '5' && s[i + 3] == '0') {

                } else {
                    flag = 0; break;
                }
            }
            if (flag) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}