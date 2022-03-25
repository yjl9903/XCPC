#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef unsigned long long ll;
const int maxn = 100000 + 5;

int prime[maxn], sum[maxn], cnt = 0;
ll a, b;

ll gcd(ll a, ll b){return b == 0 ? a : gcd(b, a % b);}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> a >> b; ms(sum, 0);
        if (a == b){
            cout << 0 << endl; continue;
        }        
        if (a == 1 || a > b || b % a){
            cout << -1 << endl; continue;
        }
        ll res = 0;
        int flag = 0;
        while (a != b){
            ll k = gcd(b / a, a);
            if (k == 1){
                flag = 1; break;
            }
            a *= k;
            res++;
        }
        if (flag) cout << -1 << endl;
        else cout << res << endl;
    }
    return 0;
}