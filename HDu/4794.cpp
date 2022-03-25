#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long LL;
const int maxn = 100000;
const int M = 2;

struct Matrix{
    LL m[M][M];
} A, I = {1, 0, 0, 1};
Matrix multi(Matrix a, Matrix b, LL mod){
    Matrix c;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            c.m[i][j] = 0;
            for (int k = 0; k < M; k++) c.m[i][j] = (c.m[i][j] % mod + (a.m[i][k] % mod) * (b.m[k][j] % mod) % mod) % mod;
            c.m[i][j] %= mod;
        }
    }
    return c;
}
Matrix power(Matrix a, LL k, LL mod){
    Matrix ans = I, p = a;
    while (k){
        if (k & 1) ans = multi(ans, p, mod);
        k >>= 1; p = multi(p, p, mod);
    }
    return ans;
}
void init(){
    A.m[0][0] = A.m[0][1] = A.m[1][0] = 1;
    A.m[1][1] = 0;
}

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL qpow(LL a, LL b, LL c){
    LL res = 1;
    a = a % c;
    while (b){
        if (b & 1) res = res * a % c;
        b >>= 1; a = a * a % c;
    }
    return res;
}

LL w[maxn], c;
LL cal(LL p){
    if (p == 2) return 3;
    if (p == 3) return 8;
    if (p == 5) return 20;
    LL ans = 1, n;
    if (qpow(5, (p - 1) >> 1, p) == 1) n = p - 1;
    else n = 2 * p + 2;
    c = 0;
    for (LL i = 1; i * i <= n; i++) if (n % i == 0){
        LL x = i, y = n / i;
        Matrix t = power(A, x - 1, p);
        LL f1 = (t.m[0][0] % p + t.m[0][1] % p) % p, f2 = (t.m[1][0] % p + t.m[1][1] % p) % p;
        if (f1 == 1 && f2 == 0) return x;
        if (x != y) w[c++] = y;
    }
    while (c){
        Matrix t = power(A, w[--c] - 1, p);
        LL f1 = (t.m[0][0] % p + t.m[0][1] % p) % p, f2 = (t.m[1][0] % p + t.m[1][1] % p) % p;
        if (f1 == 1 && f2 == 0) return w[c];
    }
    return 1;
}

LL findLoop(LL n){
    LL x = n, res = 1, l = LL(sqrt(n));
    for (LL i = 2; i * i <= x; i++)
        if (x % i == 0){
            LL t = 1;
            while (x % i == 0)
                x /= i, t *= i;
            t = t / i * cal(i);
            res = res / gcd(res, t) * t;
        }
    if (x > 1){
        LL t = cal(x);
        res = res / gcd(res, t) * t;
    }
    return res;
}

int main(){
    init(); LL n;
    while (cin >> n)
        if (n == 2) cout << 3 << endl;
        else cout << findLoop(n) / 2 << endl;
    return 0;
}