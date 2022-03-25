#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 200907;

struct Matrix{
    ll m[3][3];
    Matrix(){
        ms(m, 0);
    }
    Matrix operator * (const Matrix& b)const{
        Matrix c;
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++){
            c.m[i][j] = 0;
            for (int k = 0; k < 3; k++) c.m[i][j] = (c.m[i][j] + m[i][k] * b.m[k][j] % mod) % mod;
        }
        return c;
    }
}f, I;

Matrix qpow(Matrix a, int m){
    Matrix r = I;
    while (m > 0){
        if (m & 1) r = r * a;
        m >>= 1;
        a = a * a;
    }
    return r;
}

int n;

int main(){
    I.m[0][0] = I.m[1][1] = I.m[2][2] = 1;
    f.m[0][0] = 1; f.m[0][1] = 2; f.m[0][2] = 1;
    f.m[1][0] = 1; f.m[2][2] = 1;
    while (~scanf("%d", &n) && n){
        Matrix ans = f;
        if (n <= 1) {
            puts("1"); continue;
        }
        ans = qpow(ans, n - 1);
        ll sum = 0;
        sum += ans.m[0][0] % mod; sum %= mod;
        sum += ans.m[0][2] % mod; sum %= mod;
        printf("%lld\n", sum);
    }
    return 0;
}