#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 120 + 5;

char map[maxn][maxn];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", map[i]);
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (map[i][j] == 'B'){
                if (x1 == -1){
                    x1 = i; y1 = j;
                }
                x2 = i; y2 = j;
            }
        }
    }
    printf("%d %d\n", (x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1);
    return 0;
}