#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 10;

char a[maxn], b[maxn]; 
int plen, slen, nxt[maxn];

void getnxt(){
    int k = -1, i = 0; nxt[0] = -1;
    while (i < plen){
        if (k == -1 || a[k] == a[i]){
            i++, k++; 
            nxt[i] = k;
        }
        else k = nxt[k];
    }
}
int kmp(){
    getnxt();
    int i = 0, j = 0, res = 0;
    while (i < slen && j < plen){
        if (j == -1 || a[j] == b[i]) i++, j++;
        else j = nxt[j];
        if (j == plen){
            res++;
            // i--, j--;
            j = nxt[j];
        }
    }
    return res;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s%s", a, b);
        plen = strlen(a); slen = strlen(b);
        int res = kmp();
        printf("%d\n", res);
    }
    return 0;
}