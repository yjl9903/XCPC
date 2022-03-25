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

char a[maxn], b[maxn];

int nxt[maxn];
void getnxt(char* s) {
    int len = strlen(s), k = -1, i = 0; nxt[0] = -1;
    while (i < len) {
        if (k == -1 || s[k] == s[i]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
}
int kmp(char* s, char* p) {
    getnxt(p);
    int slen = strlen(s), plen = strlen(p), i = 0, j = 0, cnt = 0;
    while (i < slen) {
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = nxt[j];
        if (j == plen) {
            cnt++; j = nxt[j];
        }
    }
    return cnt;
}

int main(){
    scanf("%s%s", a, b);
    cout << kmp(a, b) << endl;
    return 0;
}