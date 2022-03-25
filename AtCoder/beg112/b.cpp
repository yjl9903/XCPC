#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int inf = 1 << 30;

int n, t;

int main(){
    cin >> n >> t;
    int mc = inf;
    for (int i = 0; i < n; i++){
        int t1, t2; cin >> t1 >> t2;
        if (t2 <= t) {
            mc = min(mc, t1);
        }
    }
    if (mc == inf) puts("TLE");
    else printf("%d", mc);
    return 0;
}