// HDu1042 N!

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int a[maxn], n, m, k;

int main(){
    while (~scanf("%d%d", &k, &m)){
        ms(a, 0);
        a[0] = 1;
        int cnt = 1, res = 0;

        while (true){
            if (a[k - 1] == 7){
                break;
            }
            int g = 0, tmp = 0;
            for (int j = 0; j < cnt; j++){
                tmp = a[j] * m + g;
                a[j] = tmp % 10;
                g = tmp / 10;
            }
            while (g){
                a[cnt++] = g % 10;
                g /= 10;
            }
            res++;
        }
        printf("%d\n", res);
    }
    return 0;
}