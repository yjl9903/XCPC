#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

char s[maxn], p[maxn];
int n, slen, plen, nxt[maxn];

void getnxt(int len, char s[]){
    // int i = 0, j = -1; nxt[0] = -1;
    // while (i < plen){
    //     if (j == -1 || p[i] == p[j]) nxt[++i] = ++j;
    //     else j = nxt[j];
    // }
    nxt[1] = 0;
    for (int i = 2; i <= len; i++) {
        int cur = nxt[i - 1];
        while (cur > 0 && s[cur + 1] != s[i])
            cur = nxt[cur];
        if (s[cur + 1] == s[i])
            ++cur;
        nxt[i] = cur;
    }
}
void kmp(){
    getnxt(plen, p);
    int cur = 0;
    for (int i = 1; i <= slen; i++) {
        while (cur > 0 && s[i] != p[cur + 1]) cur = nxt[cur];
        if (p[cur + 1] == s[i]) cur++;
        if (cur == plen) {
            printf("%d\n", i - cur + 1);
            cur = nxt[cur];
        }
    }
    for (int i = 1; i <= plen; i++) printf("%d ", nxt[i]);
    // int i = 0, j = 0;
    // while (i < slen && j < plen){
    //     if (j == -1 || s[i] == p[j]) i++, j++;
    //     else j = nxt[j];
    //     if (j == plen){
    //         printf("%d\n", i - plen + 1);
    //         j = nxt[j];
    //     }
    // }
    // for (int i = 1; i <= plen; i++)
    //     printf("%d%c", nxt[i], " \n"[i == plen]);
}

int main(){
    scanf("%s%s", s + 1, p + 1); 
    slen = strlen(s + 1); plen = strlen(p + 1);
    kmp();
    return 0;
}