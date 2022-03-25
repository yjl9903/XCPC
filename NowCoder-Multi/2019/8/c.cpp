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
const int maxn = 2048 + 5;

int n;
int s[maxn][maxn];

int main() {
    cin >> n;
    s[1][1] = s[1][2] = s[2][1] = 1; s[2][2] = -1;
    for (int i = 2; i <= n; i += i) {
        for (int j = i + 1; j <= i + i; j++) {
            for (int k = 1; k <= i; k++) {
                s[j][k] = s[j - i][k];
                s[k][j] = s[k][j - i];
            }
        }
        for (int j = i + 1; j <= i + i; j++) {
            for (int k = i + 1; k <= i + i; k++) {
                s[j][k] = -s[j - i][k - i];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d%c", s[i][j], j == n ? '\n' : ' ');
        }
    }
    return 0;
}