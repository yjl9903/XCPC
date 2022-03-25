#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll a, b, x, y;

ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}

int main(){
    scanf("%I64d%I64d%I64d%I64d", &a, &b, &x, &y);
    ll q = gcd(x, y);
    x /= q; y /= q;
    ll k1 = a / x, k2 = b / y;
    printf("%I64d", min(k1, k2));
    return 0;
}