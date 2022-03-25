#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, a[maxn][maxn], b[maxn][maxn];

int main(){
    while (cin >> n >> m){
        int x;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> b[i][j], a[i][j] = abs(b[i][j]);
        int r = 1, c = 1, res = a[1][1];
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++){
            if (a[i][j] > res){
                res = a[i][j];
                r = i; c = j;
            }
        }
        cout << r << ' ' << c << ' ' << b[r][c] << endl;
    }
    return 0;
}