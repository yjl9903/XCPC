#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}
int lcm(int a, int b){return a / gcd(a, b) * b;}
int n;

int main(){
    while (cin >> n){
        int x, ans; cin >> ans; n--;
        while (n--){
            cin >> x;
            ans = lcm(ans, x);
        }
        cout << ans << endl;
    }
    return 0;
}