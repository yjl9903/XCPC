#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50000 + 5;

char s[maxn], t[maxn];
int nxt[maxn], extend[maxn];

void getnxt(char *s){
    int n = strlen(s), p = 0, k = 1; nxt[0] = n;
    while (p + 1 < n && s[p] == s[p + 1]) p++;
    nxt[1] = p;
    for (int i = 2; i < n; i++){
        p = k + nxt[k] - 1;
        if (i + nxt[i - k] <= p) nxt[i] = nxt[i - k];
        else {
            int j = max(p - i + 1, 0);
            while (i + j < n && s[i + j] == s[j]) j++;
            nxt[i] = j; k = i;
        }
    }
}
// t = text, s = template
// len(extend[]) = len(t), len(nxt[]) = len(s)
void exkmp(char *t, char *s){ 
    getnxt(s); int tlen = strlen(t), slen = strlen(s), p = 0, k = 0;
    while (p < tlen && p < slen && t[p] == s[p]) p++;
    extend[0] = p;
    for (int i = 1; i < tlen; i++){
        p = k + extend[k] - 1;
        if (i + nxt[i - k] <= p) extend[i] = nxt[i - k];
        else {
            int j = max(p - i + 1, 0);
            while (i + j < tlen && j < slen && t[i + j] == s[j]) j++;
            extend[i] = j; k = i;
        }
    }
}

int main(){
    while (~scanf("%s%s", s, t)){
        exkmp(t, s); int r = 0, n = strlen(t);
        for (int i = 0; i < n; i++){
            if (extend[i] + i == n){
                r = extend[i]; break;
            }
        }
        s[r] = 0;
        if (r == 0) puts("0");
        else printf("%s %d\n", s, r);
    }
    return 0;
}