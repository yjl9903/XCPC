#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, len, tot;
char s[maxn], a[maxn], b[maxn];

int dfs2(int i, int j){
    if (i == n && j == len) return 1;
    else if (i == n) return 0;
    else if (j == len) return 0;
    for (int k = 0; k <= 9; k++){
        a[i] = k + '0';
        int tj = j, flag = 1;
        for (int l = 0; l < m; l++){
            int x = k * (b[l] - '0');
            if (x < 10){
                if (s[tj] != x + '0') {
                    flag = 0; break;
                }
                tj++;
            }
            else {
                if (s[tj] - '0' != x / 10 || s[tj + 1] - '0' != x % 10){
                    flag = 0; break;
                }
                tj += 2;
            }
        }
        if (flag && dfs2(i + 1, tj)) return 1;
    }
    return 0;
}
int dfs(int i, int j){
    if (i == m) return j;
    if (j == len) return 0;
    int x = s[j] - '0';
    if (x % tot == 0){
        b[i] = '0' + (x / tot);
        int r = dfs(i + 1, j + 1);
        if (r) return r;
    }
    if (x && j + 1 < len){
        int y = s[j + 1] - '0';
        x = x * 10 + y;
        if (x % tot == 0 && x / tot <= 9){
            b[i] = '0' + (x / tot);
            int r = dfs(i + 1, j + 2);
            if (r) return r;
        }
    }
    return 0;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(a, 0); ms(b, 0);
        scanf("%d%d%s", &n, &m, s); len = strlen(s);
        if (1ll * n * m > len){
            puts("Impossible"); continue;
        }
        int flag = 0;
        for (int i = 1; i <= 9; i++){
            a[0] = i + '0'; tot = i;
            int r = dfs(0, 0);
            if (r){
                // cout << b << endl;
                if (dfs2(1, r)) {
                    flag = 1; break;
                }
            }
        }
        if (flag) printf("%s %s\n", a, b);
        else puts("Impossible");
    }
    return 0;
}