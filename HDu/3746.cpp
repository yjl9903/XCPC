#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];
int len, nxt[maxn];

void getnxt(){
    int i = 0, j = -1; nxt[0] = -1;
    while (i < len && j < len){
        if (j == -1 || s[i] == s[j]) i++, j++, nxt[i] = j;
        else j = nxt[j];
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        len = strlen(s); getnxt();
        int l = len - nxt[len], res = l;
        while (res < len) res += l;
        if (l == len) res += l;
        printf("%d\n", res - len);
    }
    return 0;
}