#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, c[maxn], a[maxn];

int main(){
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < m; i++) cin >> a[i];
    int i = 0, j = 0, res = 0;
    while (i < n){
        if (a[j] >= c[i]){j++; res++;}
        i++;
    }
    cout << res;
    return 0;
}