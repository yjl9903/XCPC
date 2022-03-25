#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 5200 + 5;

int n, map[maxn][maxn], pre[maxn];
char s[maxn];
int f[256];

int get(int x, int y, int l) {
    return map[x][y] + map[x - l][y - l] - map[x][y - l] - map[x - l][y];
}

int main(){
    for (int i = 0; i <= 9; i++) f[i + '0'] = i;
    for (int i = 0; i <= 5; i++) f[i + 'A'] = 10 + i;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n / 4; j++) {
            int x = f[s[j]];
            map[i][4 * j - 3] = (x & 8) >> 3;
            map[i][4 * j - 2] = (x & 4) >> 2;
            map[i][4 * j - 1] = (x & 2) >> 1;
            map[i][4 * j] = (x & 1);
        }
    }
    // for (int i = 1; i <= n; i++, puts("")) for (int j = 1; j <= n; j++) putchar(map[i][j] + '0');
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        pre[j] = pre[j - 1] + map[i][j];
        map[i][j] += pre[j - 1] + map[i - 1][j];
    }
    // for (int i = 1; i <= n; i++, puts("")) for (int j = 1; j <= n; j++) printf("%d ", map[i][j]);
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (n % i) continue;
        int flag = 1;
        for (int j = i; j <= n; j += i) for (int k = i; k <= n; k += i) {
            int x = get(j, k, i);
            if (x == 0 || x == i * i);
            else {
                flag = 0; break;
            }
        }
        if (flag) ans = i;
    }
    cout << ans << endl;
    return 0;
}