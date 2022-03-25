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
const int maxn = 500 + 5;

int h, w, cnt;
char s[maxn][maxn];

int check(int x, int y) {
    if (s[x][y] == '.') return 0;
    if (x == 1 || x == h || y == 1 || y == w) return 0;
    if (s[x - 1][y] == '.' || s[x + 1][y] == '.' || s[x][y + 1] == '.' || s[x][y - 1] == '.') return 0;
    int tot = 1;
    int tx = x - 1, ty = y;
    while (tx >= 1 && s[tx][ty] == '*') {
        tot++; tx--;
    }
    tx = x + 1;
    while (tx <= h && s[tx][ty] == '*') {
        tot++; tx++;
    }
    tx = x; ty = y + 1;
    while (ty <= w && s[tx][ty] == '*') {
        tot++; ty++;
    }
    ty = y - 1;
    while (ty >= 1 && s[tx][ty] == '*') {
        tot++; ty--;
    }
    return tot == cnt;
}

int main() {
    cin >> h >> w;
    for (int i = 1; i <= h; i++) cin >> s[i] + 1;
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) if (s[i][j] == '*') cnt++;
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) {
        if (check(i, j)) return puts("YES"), 0;
    }
    puts("NO");
    return 0;
}