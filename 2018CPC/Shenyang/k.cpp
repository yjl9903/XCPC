#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[200];

bool isprime(int x){
    if (x <= 3) return 1;
    if (x == 5 || x == 7) return 1;
    return false;
}

int tab[20] = {1, 2, 3, 5, 7, 11, 13, 17, 23, 31, 37, 53, 71, 73, 113, 131, 137, 173, 311, 317};

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        bool flag = 1;
        int len = strlen(s);
        printf("Case #%d: ", ++kase);
        if (len >= 4) {
            puts("317"); continue;
        }
        int x = 0;
        for (int i = 0; i < len; i++) x = x * 10 + s[i] - '0';
        // printf("%d\n", x);
        for (int i = 19; i >= 0; i--){
            if (x >= tab[i]){
                printf("%d\n", tab[i]); break;
            }
        }
    }
    return 0;
}