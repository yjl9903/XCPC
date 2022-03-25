#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1 << 21;
const double pi = acos(-1.0);

struct complex{
    double x, y;
    complex(double a = 0, double b = 0):x(a), y(b){}
    complex operator+(const complex& b){return complex{x + b.x, y + b.y};}
    complex operator-(const complex& b){return complex{x - b.x, y - b.y};}
    complex operator*(const complex& b){return complex{x * b.x - y * b.y, x * b.y + y * b.x};}
}a[maxn], b[maxn]; int rev[maxn];
void fft(int n, complex a[], int op = 1){
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < n; i <<= 1){
        complex t(cos(pi / i), op * sin(pi / i));
        for (int j = 0; j < n; j += (i << 1)){
            complex w(1, 0);
            for (int k = 0; k < i; k++, w = w * t){
                complex x = a[j + k], y = w * a[j + k + i];
                a[j + k] = x + y; a[j + k + i] = x - y;
            }
        }
    } 
    if (op == -1) for (int i = 0; i < n; i++) a[i].x /= n, a[i].y /= n;
}
void mul(int n, complex a[], int m, complex b[], int ans[]){
    int l = 0, lim = 1; while (lim <= n + m) l++, lim <<= 1; 
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    fft(lim, a); fft(lim, b);
    for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
    fft(lim, a, -1);
    for (int i = 0; i <= n + m; i++) ans[i] = (int)(a[i].x + 0.5);
}
int ans[maxn];

int main(){
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0, x; i <= n; i++) scanf("%d", &x), a[i] = complex(x);
    for (int i = 0, x; i <= m; i++) scanf("%d", &x), b[i] = complex(x);
    mul(n, a, m, b, ans);
    for (int i = 0; i <= n + m; i++) printf("%d ", ans[i]);
    return 0;
}