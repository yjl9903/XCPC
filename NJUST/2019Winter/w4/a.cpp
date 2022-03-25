#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500 + 5;

int r, c;
char map[maxn][maxn];

int main(){
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; i++) scanf("%s", map[i] + 1);
    int flag = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (map[i][j] == 'W') {
                if (map[i + 1][j] == 'S' || map[i - 1][j] == 'S' || map[i][j + 1] == 'S' || map[i][j - 1] == 'S') {
                    flag = 1; break;
                }
                if (map[i + 1][j] == '.') map[i + 1][j] = 'D';
                if (map[i - 1][j] == '.') map[i - 1][j] = 'D';
                if (map[i][j + 1] == '.') map[i][j + 1] = 'D';
                if (map[i][j - 1] == '.') map[i][j - 1] = 'D';
            }
        }
        if (flag) break;
    }
    if (flag) puts("No");
    else {
        puts("Yes");
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) putchar(map[i][j]);
            puts("");
        }
    }
    return 0;
}