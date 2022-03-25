#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;

char s[maxn][2005], vis[maxn];
int n, nxt[2005];

void getnxt(char ptr[]){
    int len = strlen(ptr), k = -1, i = 0; nxt[0] = -1;
    while (i < len - 1){
        if (k == -1 || ptr[k] == ptr[i]) i++, k++, nxt[i] = k;
        else k = nxt[k]; 
    }
}
int kmp(char str[], char ptr[]){
    getnxt(ptr);
    int i = 0, j = 0, slen = strlen(str), plen = strlen(ptr);
    while (i < slen && j < plen){
        if (j == -1 || str[i] == ptr[j]) i++, j++;
        else j = nxt[j]; 
    }
    if (j == plen) return i - j;
    return -1;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); ms(vis, 0);
        for (int i = 0; i < n; i++) scanf("%s", s[i]);
        int res = -1, flag = 0;

        for (int i = n - 1; i > 0; i--){
            if (kmp(s[i], s[i - 1]) != -1) vis[i - 1] = 1;
        }

        for (int i = n - 1; i >= 0; i--){ 
            for (int j = 0; j < i; j++){
                if (vis[j]) continue;
                // flag = kmp(s[i], s[j]);
                // printf("%d %d %d\n", i, j, res);
                if (kmp(s[i], s[j]) == -1){
                    res = i; flag = 1; 
                    printf("Case #%d: %d\n", ++kase, res + 1);
                    break;
                }
            }
            if (flag) break;
        }
        if (!flag) printf("Case #%d: -1\n", ++kase);
    }
    return 0;
}