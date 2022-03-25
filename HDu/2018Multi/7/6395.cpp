#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 1000000007;

struct Matrix{
    ll m[3][3];
    Matrix(){
        ms(m, 0);
    }
}I;
Matrix mul(Matrix a,Matrix b){
    Matrix c;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            c.m[i][j]=0;
            for(int k = 0; k < 3; k++){
                c.m[i][j] += (a.m[i][k] * b.m[k][j]) % mod;
                c.m[i][j] %= mod;
            }
        }
    }
    return c;
}
Matrix qpow(Matrix m, ll n){
    Matrix b = I;
    while (n > 0){
        if (n & 1) b = mul(b, m);
        n >>= 1;
        m = mul(m, m);
    }
    return b;
}

ll a, b, c, d, p, n;
Matrix init(ll x){
    Matrix f;
    f.m[0][0] = 0; f.m[0][1] = 1; f.m[0][2] = 0;
    f.m[1][0] = c; f.m[1][1] = d; f.m[1][2] = x;
    f.m[2][0] = 0; f.m[2][1] = 0; f.m[2][2] = 1;
    return f;
}

int main(){
    I.m[0][0] = I.m[1][1] = I.m[2][2] = 1;
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &p, &n);
        if (n == 1){
            printf("%lld\n", a);
            continue;
        }
        else if (n == 2){
            printf("%lld\n", b);
            continue;
        }
        if (n < p){
            Matrix ans; ans.m[0][0] = a; ans.m[1][0] = b; ans.m[2][0] = 1;
            for (ll i = 3; i <= n; i = p / (p / i) + 1){
                Matrix tmp;
                if (n <= p / (p / i)) tmp = qpow(init(p / i), n - i + 1);
                else tmp = qpow(init(p / i), p / (p / i) + 1 - i);
                ans = mul(tmp, ans);
            }
            printf("%lld\n", ans.m[1][0]);
        }
        else{
            Matrix ans; ans.m[0][0] = a; ans.m[1][0] = b; ans.m[2][0] = 1;
            for (ll i = 3; i <= p; i = p / (p / i) + 1){
                Matrix tmp;
                tmp = qpow(init(p / i), p / (p / i) + 1 - i);
                ans = mul(tmp, ans);
            }
            Matrix tmp = init(0); tmp.m[1][2] = 0;
            tmp = qpow(tmp, n - max(p, 2ll));
            ans = mul(tmp, ans);
            printf("%lld\n", ans.m[1][0]);
        }
    }
    return 0;
}