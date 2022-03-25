#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int m[maxn][maxn], n;

int main(){
    m[0][0] = 0; m[1][0] = m[1][1] = 1; m[0][1] = -1;
    for (int i = 2; i < 200; i += 2){
        for (int j = 0; j < i + 2; j++) m[i + 1][j] = m[j][i + 1] = 1;
        m[i + 1][i] = 0;
        for (int j = 0; j < i + 1; j++) m[i][j] = m[j][i] = -1;
    }
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        if (n % 2){
            printf("impossible\n"); continue;
        }
        printf("possible\n");
        for (int i = 0; i < n; i++){
            printf("%d", m[i][0]);
            for (int j = 1; j < n; j++){
                printf(" %d", m[i][j]);
            }
            puts("");
        }
    }
    return 0;
}