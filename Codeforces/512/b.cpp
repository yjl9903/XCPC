#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, d, m;

int main(){
    cin >> n >> d >> m;
    for (int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        if (x + y <= 2 * n - d && x + y >= d && y - x >= -d && y - x <= d){
            puts("YES");
        }
        else puts("NO");
    }
    return 0;
}