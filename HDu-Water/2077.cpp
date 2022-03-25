#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
const int maxn = 1000 + 5;

LL f[25], g[25];

int main(){
    g[1] = 1; f[1] = 2;
    for (int i = 2; i <= 20; i++) g[i] = 3 * g[i - 1] + 1;
    for (int i = 2; i <= 20; i++) f[i] = 2 * g[i - 1] + 2;
    int n;
    int T; cin >> T;
    while (T--){
        cin >> n; cout << f[n] << endl;
    }
    return 0;
}