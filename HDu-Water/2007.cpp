#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll x, y;

int main(){
    while (cin >> x >> y){
        if (x > y) swap(x, y);
        ll s1 = 0, s2 = 0;
        for (ll i = x; i <= y; i++){
            if (i % 2) s2 += i * i * i;
            else s1 += i * i;
        }
        cout << s1 << ' ' << s2 << endl;
    }
    return 0;
}