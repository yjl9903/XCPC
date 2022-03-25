#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    while (cin >> n){
        ll x, res = 1;
        while (n--){
            cin >> x;
            if (x % 2) res *= x;
        }
        cout << res << endl;
    }
    return 0;
}