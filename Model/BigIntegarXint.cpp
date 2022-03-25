// HDu1042 N!

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int a[maxn], n;

int main(){
    while (~scanf("%d", &n)){
        a[0] = 1;
        int cnt = 1;
        for (int i = 1; i <= n; i++){
            int g = 0, tmp = 0;
            for (int j = 0; j < cnt; j++){
                tmp = a[j] * i + g;
                a[j] = tmp % 10000;
                g = tmp / 10000;
            }
            while (g){
                a[cnt++] = g % 10000;
                g /= 10000;
            }
        }
        printf("%d", a[cnt - 1]);
        for (int i = cnt - 2; i >= 0; i--){
            printf("%04d", a[i]);
        }
        printf("\n");
    }
    return 0;
}