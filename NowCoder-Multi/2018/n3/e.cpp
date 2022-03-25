#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

char p[maxn];
int len, nxt[maxn];

void getnxt(){
    int k = -1, i = 0; nxt[0] = -1;
    while (i < len){
        if (k == -1 || p[k] == p[i]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
}

int main(){
    scanf("%s", p);
    len = strlen(p); getnxt();
    int l = len - nxt[len - 1] - 1;
    if (len % l || nxt[len - 1] == 0) l = len;
    printf("%d\n", l);
    for (int i = 0; i < l; i++){
        printf("%d", len / l);
        for (int j = i; j < len; j += l){
            printf(" %d", j);
        }
        puts("");
    }
    return 0;
}