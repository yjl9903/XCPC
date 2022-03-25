#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int cube[10][6], tmp[10][6];

bool check(){
    for (int i = 1; i <= 6; i++){
        int flag = cube[i][1];
        for (int j = 2; j <= 4; j++){
            if (cube[i][j] != flag) return false;
        }
    }
    return true;
}

bool solve(){
    memcpy(tmp, cube, sizeof cube); int t, t2;
    t = cube[1][1]; cube[1][1] = cube[1][3]; cube[1][3] = cube[1][4]; cube[1][4] = cube[1][2]; cube[1][2] = t;
    t = cube[5][2]; t2 = cube[5][4]; 
    cube[5][2] = cube[2][1]; cube[5][4] = cube[2][2]; 
    cube[2][1] = cube[6][3]; cube[2][2] = cube[6][1]; cube[6][3] = cube[4][4]; cube[6][1] = cube[4][3];
    cube[4][4] = t; cube[4][3] = t2;
    if (check()) return true;

    memcpy(cube, tmp, sizeof cube);
    t = cube[1][1]; cube[1][1] = cube[1][2]; cube[1][2] = cube[1][4]; cube[1][4] = cube[1][3]; cube[1][3] = t;
    t = cube[5][2]; t2 = cube[5][4]; 
    cube[5][2] = cube[4][4]; cube[5][4] = cube[4][3]; 
    cube[4][4] = cube[6][3]; cube[4][3] = cube[6][1]; cube[6][3] = cube[2][1]; cube[6][1] = cube[2][2];
    cube[2][1] = t; cube[2][2] = t2;
    if (check()) return true;

    memcpy(cube, tmp, sizeof cube);
    t = cube[2][1]; cube[2][1] = cube[2][2]; cube[2][2] = cube[2][4]; cube[2][4] = cube[2][3]; cube[2][3] = t;
    t = cube[3][1]; t2 = cube[3][2];
    cube[3][1] = cube[5][4]; cube[3][2] = cube[5][3]; 
    cube[5][4] = cube[1][4]; cube[5][3] = cube[1][3]; cube[1][4] = cube[6][4]; cube[1][3] = cube[6][3];
    cube[6][4] = t; cube[6][3] = t2;
    if (check()) return true;

    memcpy(cube, tmp, sizeof cube);
    t = cube[2][1]; cube[2][1] = cube[2][3]; cube[2][3] = cube[2][4]; cube[2][4] = cube[2][2]; cube[2][2] = t;
    t = cube[3][1]; t2 = cube[3][2];
    cube[3][1] = cube[6][4]; cube[3][2] = cube[6][3]; 
    cube[6][4] = cube[1][4]; cube[6][3] = cube[1][3]; cube[1][4] = cube[5][4]; cube[1][3] = cube[5][3];
    cube[5][4] = t; cube[5][3] = t2;
    if (check()) return true;

    memcpy(cube, tmp, sizeof cube);
    t = cube[6][1]; cube[6][1] = cube[6][3]; cube[6][3] = cube[6][4]; cube[6][4] = cube[6][2]; cube[6][2] = t;
    t = cube[1][2]; t2 = cube[1][4]; 
    cube[1][2] = cube[2][2]; cube[1][4] = cube[2][4];  
    cube[2][2] = cube[3][2]; cube[2][4] = cube[3][4]; cube[3][2] = cube[4][2]; cube[3][4] = cube[4][4];
    cube[4][2] = t; cube[4][4] = t2;
    if (check()) return true;

    memcpy(cube, tmp, sizeof cube);
    t = cube[6][1]; cube[6][1] = cube[6][2]; cube[6][2] = cube[6][4]; cube[6][4] = cube[6][3]; cube[6][3] = t;
    t = cube[1][2]; t2 = cube[1][4]; 
    cube[1][2] = cube[4][2]; cube[1][4] = cube[4][4];  
    cube[4][2] = cube[3][2]; cube[4][4] = cube[3][4]; cube[3][2] = cube[2][2]; cube[3][4] = cube[2][4];
    cube[2][2] = t; cube[2][4] = t2;
    if (check()) return true;

    return false;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        for (int i = 1; i <= 6; i++) for (int j = 1; j <= 4; j++) scanf("%d", &cube[i][j]);
        if (check()) puts("YES");
        else {
            if (solve()) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}