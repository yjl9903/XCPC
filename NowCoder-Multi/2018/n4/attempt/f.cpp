#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

char map[maxn][maxn];
int n, m;

int check(int t){
    for (int i = 1; i <= m / 2; i++){
        if (map[t][i] != map[t][m + 1 - i])
            return m / 2 - i + 1;
    }
    return 0;
}
int check2(int t){
    for (int i = 1; i <= n / 2; i++){
        if (map[i][t] != map[n + 1 - i][t])
            return n / 2 - i + 1;
    }
    return 0;
}
bool judge(int x, int y){ // x竖直，y水平
    // for (int i = 2; i <)
    return 1;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%s", map[i] + 1);
        if (check(1) || check(m) || check2(1) || check2(n)){
            printf("0\n"); continue;
        }

        int res = 0;
        for (int i = n / 2 - 1; i > 0; i--) {
            for (int j = m / 2 - 1; j > 0; j--){
                // res += judge(i, j);
                res++;
                if (check2(m / 2 - j + 1) || check2(m / 2 + j)) break;
            }
            if (check(n / 2 - i + 1) || check(n / 2 + i)) break;
        }
        printf("%d\n", res);
    }
    return 0;
}