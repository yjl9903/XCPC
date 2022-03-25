#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000000 + 5;

int a, b, c, d, n, m;
int cal(int x){
    int l = 0, r = 1e9;
    while (l <= r){
        int m = l + r >> 1;
        ll t = 1ll * m * (m - 1) / 2;
        if (t <= 1ll * x) l = m + 1;
        else r = m - 1;
    }
    return r;
}
char s[maxn];

int main(){
    cin >> a >> b >> c >> d;
    n = cal(a); m = cal(d);
    if (b == 0 && c == 0){
        if (n == 1 && m == 1) return puts("1"), 0;
        else if (n != 1 && m == 1){
            if (n * (n - 1) / 2 == a) {
                for (int i = 0; i < n; i++) putchar('0');
                return 0;
            }
            return puts("impossible"), 0;
        }
        else if (m != 1 && n == 1){
            if (m * (m - 1) / 2 == d) {
                for (int i = 0; i < m; i++) putchar('1');
                return 0;
            }
            return puts("impossible"), 0;
        }
    }
    if (n * (n - 1) / 2 != a || m * (m - 1) / 2 != d || b + c != n * m) return puts("impossible"), 0;

    int p = 0, k1 = c / n, k2 = c % n;
    for (int i = 0; i < k1; i++) s[p++] = '1', m--;
    for (int i = 0; i < n - k2; i++) s[p++] = '0';
    if (m) s[p++] = '1', m--;
    for (int i = n - k2; i < n; i++) s[p++] = '0';
    for (int i = 0; i < m; i++) s[p++] = '1';

    cout << s << endl;
    return 0;
}