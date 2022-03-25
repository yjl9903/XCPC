#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

int n = 47, a[maxn][maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int t = j;
            for (int k = 0; k < n; k++){
                if (k) t += i;
                t %= n;
                a[k * n + t][i * n + j] = 1;
            }
        }
    }
    int m = n * n;
    for (int i = 0; i < m; i++, printf("\n")) for (int j = 0; j < m; j++) printf("%d", a[i][j]);
    return 0;
}