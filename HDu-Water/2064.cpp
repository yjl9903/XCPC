#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
const int maxn = 35 + 5;

LL f[maxn], g[maxn];

int main(){
    g[1] = 1; f[1] = 2;
    for (int i = 2; i <= 35; i++) g[i] = 3 * g[i - 1] + 1;
    for (int i = 2; i <= 35; i++) f[i] = 6 * g[i - 1] + 2;
    int n;
    while (cin >> n) cout << f[n] << endl;
    return 0;
}