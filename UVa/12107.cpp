#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

char a[3], b[3], c[5];
int len[3], maxd, cnt = 0, vis[3][5];
struct equation{
    char a[3], b[3], c[5];
}tot, res;

void check(equation x){
    for (int i = 0; i < len[0]; i++){
        if (x.a[i] == '*'){
            for (int j = (i == 0 ? 1 : 0); j <= 9; j++){
                x.a[i] = j + '0';
                check(x);
            }
            return;
        }
    }
    for (int i = 0; i < len[1]; i++){
        if (x.b[i] == '*'){
            for (int j = (i == 0 ? 1 : 0); j <= 9; j++){
                x.b[i] = j + '0';
                check(x);
            }
            return;
        }
    }
    if (cnt > 1) return;
    int a = 0, b = 0;
    for (int i = 0; i < len[0]; i++)
        a = a * 10 + x.a[i] - '0';
    for (int i = 0; i < len[1]; i++)
        b = b * 10 + x.b[i] - '0';
    int c = a * b, flag = 1, d[5], l = 0;
    while (c){
        d[l++] = c % 10;
        c /= 10;
    }
    if (l != len[2]) return;
    for (int i = 0; i < l; i++){
        if (x.c[i] != '*' && x.c[i] != '0' + d[l - 1 - i])
            flag = 0;
    }
    if (flag) cnt++;
}

int dfs(int d, int p, equation x){
    if (d == maxd){
        cnt = 0; check(x);
        if (cnt == 1){
            res = x;
            return 1;
        }
        return 0;
    }
    if (maxd - d > len[0] + len[1] + len[2] - p) return 0;

    equation t = x;
    if (p < len[0]){
        t.a[p] = '*';
        if (dfs(d + (x.a[p] == '*' ? 0 : 1), p + 1, t)) return 1;
        for (int i = (p == 0 ? 1 : 0); i <= 9; i++){
            t.a[p] = i + '0';
           if (dfs(d + (t.a[p] == x.a[p] ? 0 : 1), p + 1, t)) return 1;
        }
    }
    else if (p < len[0] + len[1]){
        p -= len[0];
        t.b[p] = '*';
        if (dfs(d + (x.b[p] == '*' ? 0 : 1), p + 1 + len[0], t)) return 1;
        for (int i = (p == 0 ? 1 : 0); i <= 9; i++){
            t.b[p] = i + '0';
            if (dfs(d + (t.b[p] == x.b[p] ? 0 : 1), p + 1 + len[0], t)) return 1;
        }
    }
    else if (p < len[0] + len[1] + len[2]){
        p -= len[0] + len[1];
        t.c[p] = '*';
        if (dfs(d + (x.c[p] == '*' ? 0 : 1), p + 1 + len[0] + len[1], t)) return 1;
        for (int i = (p == 0 ? 1 : 0); i <= 9; i++){
            t.c[p] = i + '0';
            if (dfs(d + (t.c[p] == x.c[p] ? 0 : 1), p + 1 + len[0] + len[1], t)) return 1;
        }
    }
    return 0;
}

int main(){
    int kase = 0;
    while (~scanf("%s%s%s", tot.a, tot.b, tot.c) && tot.a[0] != '0'){
        len[0] = strlen(tot.a); len[1] = strlen(tot.b); len[2] = strlen(tot.c);
        int flag = 0;
        for (maxd = 0; !flag; maxd++){
            ms(vis, 0);
            flag = dfs(0, 0, tot);
        }
        printf("Case %d: %s %s %s\n", ++kase, res.a, res.b, res.c);
    }
    return 0;
}