#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll a, b, c;
vector<int> v[2];

int main(){
    cin >> a >> b;
    int l = 0, r = 2e9;
    while (l <= r){
        int m = l + r >> 1;
        ll t = 1ll * m * (m + 1) / 2;
        if (t <= a + b) l = m + 1;
        else r = m - 1;
    }
    // cout << l << ' ' << r << endl;
    for (int i = r; i >= 1; i--){
        if (a >= i){
            a -= i; v[0].push_back(i);
        }
        else {
            b -= i; v[1].push_back(i);
        }
    }
    printf("%d\n", v[0].size());
    for (auto x : v[0]) printf("%d ", x);
    printf("\n%d\n", v[1].size());
    for (auto x : v[1]) printf("%d ", x);
    return 0;
}