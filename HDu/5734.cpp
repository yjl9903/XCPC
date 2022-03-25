#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int w[maxn], n;

ll gcd(ll a, ll b){return b == 0 ? a : gcd(b, a % b);}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n; for (int i = 0; i < n; i++){
            int x; cin >> x; w[i] = ((x >= 0) ? x : -x);
        }
        ll sum1 = 0, sum2 = 0, res = 0;
        for (int i = 0; i < n; i++){
            sum1 += 1ll * w[i]; sum2 += 1ll * w[i] * w[i];
        }
        
        ll t = 1ll * n * sum2 - sum1 * sum1, d = n;
        ll k = gcd(t, d);
        cout << t / k << '/' << d / k << endl;

    }
    return 0;
}