#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5 + 5;
const int maxc = 30;

char s[maxn][maxn];
int map[maxn][maxn], n, row[maxn][maxn], col[maxn][maxn], s1, s2, line[maxc][maxc], nxt[maxc], vis[maxc];

int find(int p){
    for (int i = 1; i <= s2; i++){
        if (!vis[i] && line[p][i]){
            vis[i] = 1;
            if (!nxt[i] || find(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
    }
    return false;
}
int match(){
    int sum = 0;
    for (int i = 1; i <= s1; i++){
        ms(vis, 0);
        if (find(i)) sum++;
    }
    return sum;
}

int main(){
    while (cin >> n && n){
        ms(s, 0); ms(line, 0); ms(nxt, 0);
        for (int i = 0; i < n; cin >> s[i++]);
        s1 = 1; s2 = 1;
        for (int i = 0; i < n; i++){
            int start = 0; while (s[i][start] == 'X' && start < n) start++;
            for (int j = start; j < n; j++){
                if (s[i][j] == '.') row[i][j] = s1;
                else if (s[i][j] == 'X'){
                    s1++;
                    while (s[i][j] == 'X' && j < n) j++;
                    j--;
                }
            }
            s1++;
        }
        for (int i = 0; i < n; i++){
            int start = 0; while (s[start][i] == 'X' && start < n) start++;
            for (int j = start; j < n; j++){
                if (s[j][i] == '.') col[j][i] = s2;
                else if (s[j][i] == 'X'){
                    s2++;
                    while (s[j][i] == 'X' && j < n) j++;
                    j--;
                }
            }
            s2++;
        }
        // for (int i = 0; i < n; i++, cout << endl) for (int j = 0; j < n; j++) cout << row[i][j] << ' '; cout << endl;
        // for (int i = 0; i < n; i++, cout << endl) for (int j = 0; j < n; j++) cout << col[i][j] << ' '; cout << endl;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (s[i][j] == '.')line[row[i][j]][col[i][j]] = 1;
        cout << match() << endl;
    }
    return 0;
}