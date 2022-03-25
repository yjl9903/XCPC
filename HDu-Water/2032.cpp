#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;

int map[maxn][maxn] = {0}, n;

int main(){
    map[1][1] = 1; 
    for (int i = 2; i <= 30; i++){
        map[i][1] = 1;
        for (int j = 2; j <= i; j++){
            map[i][j] = map[i - 1][j] + map[i - 1][j - 1];
        }
    }
    while (cin >> n){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= i; j++){
                if (j != 1) cout << ' ';
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}