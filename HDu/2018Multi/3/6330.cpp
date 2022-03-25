#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char s[maxn][maxn]; 
int a, b, c;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(s, 0);
        scanf("%d%d%d", &a, &b, &c);
        // if (c < b) swap(c, b);
        int m = 2 * a + 1 + 2 * b, n = 2 * b + 2 * c + 1;
        for (int i = 0; i < 2 * b; i += 2){
            for (int j = 0; j < m; j++) s[i][j] = s[i + 1][j] = '.';
            for (int j = 0; j < 2 * a + 1; j++) {
                if (j % 2) s[i][j + 2 * b - i] = '-';
                else s[i][j + 2 * b - i] = '+';
            }
            for (int j = 0; j < 2 * a + 1; j += 2) s[i + 1][j + 2 * b - i - 1] = '/';
            for (int j = 1; j <= i; j += 2){
                s[i][m - j] = '+';
            }
            for (int j = 1; j <= i + 1; j++){
                if (j % 2) s[i + 1][m - j] = '|';
                else s[i + 1][m - j] = '/';
            }
            if (i + 2 * b >= n){
                for (int j = 1; j <= i + 2 * b - n; j++) s[i][m - j] = '.';
            }
            if (i + 1 + 2 * b >= n){
                for (int j = 1; j <= i + 2 + 2 * b - n; j++) s[i + 1][m - j] = '.';
            }
            puts(s[i]);
            puts(s[i + 1]);
        }
        for (int i = 2 * b; i < 2 * b + 2 * c; i += 2){
            for (int j = 0; j < m; j++) s[i][j] = s[i + 1][j] = '.';
            for (int j = 0; j < 2 * a + 1; j++) 
                if (j % 2) s[i][j] = '-';
                else s[i][j] = '+';
            for (int j = 0; j < 2 * a + 1; j++)
                if (j % 2 == 0) s[i + 1][j] = '|';
            for (int j = 1; j <= 2 * b; j += 2){
                s[i][m - j] = '+';
            }
            for (int j = 1; j <= 2 * b; j++){
                if (j % 2) s[i + 1][m - j] = '|';
                else s[i + 1][m - j] = '/';
            }
            if (i + 2 * b >= n){
                for (int j = 1; j <= i + 2 * b - n; j++) s[i][m - j] = '.';
            }
            if (i + 1 + 2 * b >= n){
                for (int j = 1; j <= i + 2 + 2 * b - n; j++) s[i + 1][m - j] = '.';
            }
            puts(s[i]);
            puts(s[i + 1]);
        }
        for (int j = 0; j < 2 * a + 1; j++) 
            if (j % 2) s[n - 1][j] = '-';
            else s[n - 1][j] = '+';
        for (int j = 2 * a + 1; j < m; j++) s[n - 1][j] = '.';
        puts(s[n - 1]);
    }
    return 0;
}