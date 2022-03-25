#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char map[8][maxn];
int n;

int change(char* s){
    int x, y;
    if (s[0] >= '0' && s[0] <= '9') x = s[0] - '0';
    else x = 10 + s[0] - 'A';
    if (s[1] >= '0' && s[1] <= '9') y = s[1] - '0';
    else y = 10 + s[1] - 'A';
    return x * 16 + y;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); ms(map, 0);
        for (int i = 0; i < 8; i++) for (int j = 0; j < 6 * n - 1; j++) map[i][j] = ' ';
        char s[5];
        int tot = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 5; j++){
                scanf("%s", s);
                int m = change(s);
                for (int k = 0; k < 8; k++){
                    if (m & (1 << k)) map[k][tot] = '#';
                }
                tot++;
            }
            tot++;
        }  
        printf("Case %d:\n\n", ++kase);
        for (int i = 0; i < 7; i++) printf("%s\n", map[i]);
        puts("");
    }
    return 0;
}