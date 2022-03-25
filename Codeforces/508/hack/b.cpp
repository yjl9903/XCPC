#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}

int main(){
    for (int i = 10000; i <= 45000; i++){
        ll sum = 1ll * i * (i + 1) / 2;
        int flag = -1;
        for (ll j = 1; j <= i; j++){
            if (gcd(sum - j, j) > 1){
                flag = j; break;
            }
        }
        printf("%d: %s\n", i, flag == -1 ? "No" : "Yes");
    }
    return 0;
}