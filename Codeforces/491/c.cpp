#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, k;

int main(){
    cin >> n;
    ll l = 1, r = n, res = n / 2 + n % 2;
    while (l <= r){
        ll m = (l + r) / 2;
        ll eat = 0, rest = n;
        while (rest > 0){
            if (rest >= m)
                rest -= m, eat += m;
            else
                eat += rest, rest = 0;
            rest -= rest / 10;
        }
        // cout << m << ' ' << eat << endl;
        if (eat >= res){
            k = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    cout << k;
    return 0;
}