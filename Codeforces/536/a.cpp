#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500 + 5;

char map[maxn][maxn];
int n;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", map[i]);
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (map[i][j] == 'X' && map[i - 1][j - 1] == 'X' && map[i + 1][j - 1] == 'X' && 
                map[i - 1][j + 1] == 'X' && map[i + 1][j + 1] == 'X') ans++;
        }
    }
    cout << ans << endl;
    return 0;
}