#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 33 + 5;

ll res[maxn][2];

int main(){
    res[0][0] = 1; res[0][1] = 0;
    for (int i = 1; i <= 33; i++) {
        res[i][0] = 3 * res[i - 1][0] + 2 * res[i - 1][1];
        res[i][1] = res[i - 1][0] + res[i - 1][1];
    }
    int n;
    while (cin >> n){
        if (n == -1) break;
        cout << res[n][0] << ", " << res[n][1] << endl;
    }
    return 0;
}