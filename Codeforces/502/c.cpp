#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn] = {0};

int main(){
    scanf("%d", &n);
    if (n == 1){
        puts("1"); return 0;
    }
    if (n == 2){
        puts("2 1"); return 0;
    }
    int res = 2, m = n / 2 + 2 + n % 2;
    for (int i = 3; i < n; i++){
        int t = n / i + i;
        if (n % i) t++;
        if (t < m) res = i, m = t;
    }
    // printf("%d %d\n", m, res);
    int tot = n, c = n;
    for (int i = n % res; i >= 1; i--) a[tot--] = i;
    for (int i = n % res; i <= n; i += res){
        for (int j = i + res; j > i; j--) {
            a[tot--] = j;
            if (tot == 0) break;
        }
        if (tot == 0) break;
    }
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}