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
const int maxn = 2000 + 5;

int n, mp[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        mp[1][1] = mp[1][2] = mp[2][2] = 1;
        mp[2][1] = 0;
        for (int i = 2; i <= n; i++) {
            int len = 1 << (i - 1);
            for (int i = 1; i <= len; i++) {
                for (int j = 1; j <= len; j++) {
                    mp[i][j + len] = mp[i][j];
                    mp[i + len][j] = mp[i][j] ^ 1;
                    mp[i + len][j + len] = mp[i][j];
                }
            }
        }
        for (int i = 1; i <= (1 << n); i++) {
            for (int j = 1; j <= (1 << n); j++) {
                putchar(mp[i][j] ? 'C' : 'P');
            }
            puts("");
        }
    }
    return 0;
}