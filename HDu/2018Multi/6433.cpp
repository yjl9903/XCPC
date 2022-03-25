#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;

int a[maxn], cnt = 1;
void mul(int k){
    int g = 0, tmp = 0;
    for (int j = 0; j < cnt; j++){
        tmp = a[j] * k + g;
        a[j] = tmp % 10000;
        g = tmp / 10000;
    }
    while (g){
        a[cnt++] = g % 10000;
        g /= 10000;
    }
}
void print(){
    printf("%d", a[cnt - 1]);
    for (int i = cnt - 2; i >= 0; i--){
        printf("%04d", a[i]);
    }
    puts("");
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        a[0] = 1; cnt = 1; // init
        for (int i = 1; i <= n; i++){
            mul(2);
        }
        print();
    }
    return 0;
}