#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int map[maxn][maxn], res[maxn][maxn], n, k;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void show(){
    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            cout << char(res[i][j] - 1 + 'A');
    // cout << endl;
}

int dfs(int pos, int cnt){
    while (res[pos / n][pos % n] && pos < n * n) pos++;
    // show();
    if (pos == n * n) return 1;
    int sx = pos/ n, sy = pos % n, ey = n;
    for (int i = sx; i < n; i++) for (int j = sy; j < ey; j++){
        if (res[i][j]){
            ey = j; break;
        }
        int sum = (i - sx + 1) * (j - sy + 1);
        if (sum > 9){
            ey = j; break;
        }
        int t = 100, flag = 1;
        for (int p = sx; p <= i; p++){
            for (int q = sy; q <= j; q++){
                if (map[p][q]){
                    if (t != 100) { flag = false; break; }
                    t = map[p][q];
                }
            }
            if (!flag) break;
        }
        if (!flag) {
            ey = j; break;
        }
        if (t < sum){
            ey = j; break;
        }
        if (t > sum) continue;
        for (int p = sx; p <= i; p++) for (int q = sy; q <= j; q++)
            res[p][q] = cnt;
        if (dfs(pos + j - sy + 1, cnt + 1)) return 1;
        for (int p = sx; p <= i; p++) for (int q = sy; q <= j; q++)
            res[p][q] = 0;
    }
    return 0;
}

int main(){
    while (cin >> n >> k){
        if (!n && !k) return 0;
        for (int i = 0; i < n; i++){
            char s[maxn]; cin >> s;
            for (int j = 0; j < n; j++){
                if (s[j] == '.') map[i][j] = 0;
                else map[i][j] = s[j] - '0';
            }
        }
        ms(res, 0); ;
        dfs(0, 1);
        show();
        // for (int i = 0; i < n; i++, cout << endl)
        //     for (int j = 0; j < n; cout << char(res[i][j++] - 1 + 'A'));
        
    }
    return 0;
}