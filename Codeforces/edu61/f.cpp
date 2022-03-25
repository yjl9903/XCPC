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
const int maxn = 1000 + 5;

int n, f[maxn][maxn]; char s[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = 1e9;
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                f[l][r] = min(f[l + 1][r - 1] + 1, min(f[l + 1][r], f[l][r - 1]));
            } else {
                for (int i = l; i < r; i++) f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r]);
            }
        }
    }
    cout << f[1][n] << endl;
    return 0;
}