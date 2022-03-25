#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

char s[maxn]; int n;

int map[5][5], delx[5], dely[5];
void clear() {
    ms(delx, 0); ms(dely, 0);
    for (int i = 1; i <= 4; i++) {
        int flag = 1;
        for (int j = 1; j <= 4; j++) if (map[i][j] == 0) flag = 0;
        if (flag) delx[i] = 1;
    }
    for (int i = 1; i <= 4; i++) {
        int flag = 1;
        for (int j = 1; j <= 4; j++) if (map[j][i] == 0) flag = 0;
        if (flag) dely[i] = 1;
    }
    for (int i = 1; i <= 4; i++) {
        if (delx[i]) for (int j = 1; j <= 4; j++) map[i][j] = 0;
        if (dely[i]) for (int j = 1; j <= 4; j++) map[j][i] = 0;
    }
}

int main(){
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            for (int i = 1; i <= 4; i++) {
                if (map[1][i] == 0 && map[2][i] == 0) {
                    map[1][i] = map[2][i] = 1;
                    printf("1 %d\n", i); break;
                } else if (map[3][i] == 0 && map[4][i] == 0) {
                    map[3][i] = map[4][i] = 1;
                    printf("3 %d\n", i); break;
                }
            }
        } else if (s[i] == '1') {
            for (int i = 1; i <= 4; i++) {
                if (map[i][3] == 0 && map[i][4] == 0) {
                    map[i][3] = map[i][4] = 1;
                    printf("%d 3\n", i); break;
                }
            }
        }
        clear();
    }
    return 0;
}