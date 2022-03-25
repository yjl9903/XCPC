#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500000 + 5;

int ch[maxn][11], val[maxn], tot, flag = 0;
void insert(char* s) {
    int now = 0;
    for (int i = 0; s[i]; i++) {
        if (ch[now][s[i] - '0']) {
            now = ch[now][s[i] - '0'];
        } else {
            now = ch[now][s[i] - '0'] = ++tot;
        }
    }
    val[now]++;
}
int query(char* s) {
    int now = 0;
    for (int i = 0; s[i]; i++) {
        if (val[now]) return 1;
        now = ch[now][s[i] - '0'];
    }
    return 0;
}

int n;
char s[maxn][20];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        ms(ch, 0); ms(val, 0);
        tot = flag = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", s[i]);
            insert(s[i]);
        }
        for (int i = 0; i < n; i++) {
            if (query(s[i])) {
                flag = 1; break;
            }
        }
        if (!flag) puts("YES");
        else puts("NO");
    }
    return 0;
}