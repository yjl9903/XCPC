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
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; i++) {
            if (s[i] == 'z') {
                int f = 1;
                for (int j = 1; j < i; j++) {
                    if (s[j] != 'y') {
                        f = 0; break;
                    }
                }
                if (f) s[i] = 'b';
                break;
            }
        }
        puts(s + 1);
    }
    return 0;
}