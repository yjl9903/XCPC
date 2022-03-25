#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}

int main(){
    int T, n, kase = 0, a, b;
    cin >> T;
    while (T--){
        cin >> n >> a >> b;
        int k = gcd(a, b), res = n / k;
        cout << "Case #" << ++kase << ": " << (res % 2 != 0 ? "Yuwgna" : "Iaka") << endl;
    }
    return 0;
}