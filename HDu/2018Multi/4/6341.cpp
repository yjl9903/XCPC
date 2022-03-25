#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 16 + 5;

char s[maxn];
int a[maxn][maxn], t[maxn][maxn], res = 0, vis[2][maxn][maxn];

int f(char a){
    if (a >= '0' && a <= '9') return a - '0';
    else return a - 'A' + 10;
}
char g(int a){
    if (a < 10) return char(a) + '0';
    else return char(a - 10) + 'A';
}
void show(int a[][maxn]){
    puts("");
    for (int i = 0; i < 16; i++, puts("")) for (int j = 0; j < 16; j++) putchar(g(a[i][j]));
}

void count(){
    ms(vis, 0);
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            vis[0][i][a[i][j]]++;
            vis[1][j][a[i][j]]++;
        }
    }
}
bool check(){
    ms(vis, 0);
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            vis[0][i][a[i][j]]++;
            vis[1][j][a[i][j]]++;
            if (vis[0][i][a[i][j]] >= 2 || vis[1][j][a[i][j]] >= 2) return false;
        }
    }
    return true;
}

void add(int r, int c, int x){
    for (int i = 4 * r; i < 4 * (r + 1); i++) for (int j = 4 * c; j < 4 * (c + 1); j++) {
        vis[0][i][a[i][j]] += x; vis[1][j][a[i][j]] += x;
    }
}

int rot(int r, int c){
    for (int i = 4 * r; i < 4 * (r + 1); i++) for (int j = 4 * c; j < 4 * (c + 1); j++){
        vis[0][i][a[i][j]]--; vis[1][j][a[i][j]]--;
        // t[j - c * 4][(r + 1) * 4 - i - 1] = a[i][j];
        t[i][j] = a[4 * r + (j - 4 * c)][4 * c + (4 * (r + 1) - i - 1)];
    }
    // memcpy(t, a, sizeof a);
    int flag = 1;
    for (int i = 4 * r; i < 4 * (r + 1); i++){
        for (int j = 4 * c; j < 4 * (c + 1); j++){
            // a[i][j] = t[4 * r + (j - 4 * c)][4 * c + (4 * (r + 1) - i - 1)];
            // a[i][j] = t[i - r * 4][j - c * 4];
            a[i][j] = t[i][j];
            vis[0][i][a[i][j]]++; vis[1][j][a[i][j]]++;
            if (vis[0][i][a[i][j]] >= 2 || vis[1][j][a[i][j]] >= 2) flag = 0;
        }
    }
    // memcpy(a, t, sizeof a);
    return flag;
}

void dfs(int r, int c, int now){
    if (r == 4 && c == 0) {
        res = min(now, res);
        return;
    }
    if (now >= res) return;
    add(r, c, 1);
    for (int i = 1; i <= 4; i++){
        if (rot(r, c))
            dfs(c == 3 ? r + 1 : r, c == 3 ? 0 : c + 1, now + (i == 4 ? 0 : 4 - i));
        // show(a);
    }
    add(r, c, -1);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        for (int i = 0; i < 16; i++){
            scanf("%s", s);
            for (int j = 0; j < 16; j++) a[i][j] = f(s[j]);
        }
        // count();
        ms(vis, 0);
        res = 64; dfs(0, 0, 0);
        printf("%d\n", res);
    }
    return 0;
}