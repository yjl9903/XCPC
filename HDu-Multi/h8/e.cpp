#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[3][3], b[2][2], c[2][2];

void rot(char k){
    if (k == 'R'){
        c[0][0] = b[0][1];
        c[0][1] = b[1][1];
        c[1][1] = b[1][0];
        c[1][0] = b[0][0];
    }
    if (k == 'C'){
        c[0][0] = b[1][0];
        c[1][0] = b[1][1];
        c[1][1] = b[0][1];
        c[0][1] = b[0][0];
    }
}
void change(int x, char k){
    if (x == 1){
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) b[i][j] = a[i][j];
        rot(k);
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) a[i][j] = c[i][j];
    }
    if (x == 2){
        for (int i = 0; i < 2; i++) for (int j = 1; j < 3; j++) b[i][j - 1] = a[i][j];
        rot(k);
        for (int i = 0; i < 2; i++) for (int j = 1; j < 3; j++) a[i][j] = c[i][j - 1];
    }
    if (x == 3){
        for (int i = 1; i < 3; i++) for (int j = 0; j < 2; j++) b[i - 1][j] = a[i][j];
        rot(k);
        for (int i = 1; i < 3; i++) for (int j = 0; j < 2; j++) a[i][j] = c[i - 1][j];
    }
    if (x == 4){
        for (int i = 1; i < 3; i++) for (int j = 1; j < 3; j++) b[i - 1][j - 1] = a[i][j];
        rot(k);
        for (int i = 1; i < 3; i++) for (int j = 1; j < 3; j++) a[i][j] = c[i - 1][j - 1];
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 0; i < 3; i++){
            int x; scanf("%d", &x);
            a[i][0] = x / 100; a[i][2] = x % 10; a[i][1] = (x % 100 - x % 10) / 10;
        }
        char cmd[10];
        while (n--){
            scanf("%s", cmd);
            change(cmd[0] - '0', cmd[1]);
        }
        for (int i = 0; i < 3; i++){
            printf("%d%d%d\n", a[i][0], a[i][1], a[i][2]);
        }
    }
    return 0;
}