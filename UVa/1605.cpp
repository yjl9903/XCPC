#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

int n;
char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(){
    int kase = 0;
    while (~scanf("%d", &n)){
        if (kase++) printf("\n");
        printf("2 %d %d\n", n, n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                printf("%c", set[j]);
            printf("\n");
        }
        printf("\n");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                printf("%c", set[i]);
            printf("\n");
        }
    }
    return 0;
}