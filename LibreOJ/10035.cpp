#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1000000 + 5;

char s[maxn];
int nxt[maxn];
void getnxt(char* s) {
    int len = strlen(s), i = 0, k = -1; nxt[0] = -1;
    while (i < len) {
        if (k == -1 || s[i] == s[k]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
}

int main(){
    while (scanf("%s", s)) {
        if (s[0] == '.') return 0;
        getnxt(s);
        int len = strlen(s);
        if (len % (len - nxt[len]) == 0) cout << len / (len - nxt[len]) << endl;
        else puts("1");
    }
    return 0;
}