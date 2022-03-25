#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 500000 + 5;

char s[maxn], t[maxn], ans[maxn];
int nxt[maxn];

void getnxt() {
    int len = strlen(t), i = 0, j = -1; nxt[0] = -1;
    while (i < len) {
        if (j == -1 || t[i] == t[j]) i++, j++, nxt[i] = j;
        else j = nxt[j];
    }
}

int main() {
    scanf("%s%s", s, t);
    getnxt();
    int c[2] = {0, 0};
    for (int i = 0; s[i]; i++) c[s[i] - '0']++;
    int slen = strlen(s), tlen = strlen(t), i = 0, j = 0;
    while (i < slen && j < tlen) {
        if (j == -1) {
            if (c[t[0] - '0']) {
                ans[i] = t[0]; c[t[0] - '0']--;
            } else {
                ans[i] = (t[0] - '0' + 1) % 2 + '0';
                c[ans[i] - '0']--;
            }
            i++; j++;
        } else if (c[t[j] - '0']) {
            ans[i] = t[j]; c[t[j] - '0']--;
            i++; j++;
        } else j = nxt[j];
        if (j == tlen) j = nxt[j];
    }
    cout << ans << endl;
    return 0;
}