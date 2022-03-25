#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000 + 5;

int g[maxn][maxn], p = 47;

int main(){
    for (int i = 0; i < p; i++) for (int j = 0; j < p; j++){
        for (int k = 0; k < p; k++){
            g[i * p + j][k * p + (k * j + i) % p] = 1;
        }
    }
    puts("2000");
    for (int i = 0; i < 2000; i++, puts("")) for (int j = 0; j < 2000; j++) putchar(g[i][j] + '0');
    return 0;
}