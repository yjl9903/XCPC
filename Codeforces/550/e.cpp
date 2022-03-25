#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

char s[maxn], t[maxn];

int n, a[maxn], b[maxn], c[maxn];

void sub() {
    for (int i = n; i >= 1; i--) {
        if (t[i] >= s[i]) {
            c[i] = t[i] - s[i];
        } else {
            c[i] = t[i] - s[i] + 26;
            t[i - 1]--;
        }
    }
}
void div() {
    for (int i = 1; i <= n; i++) {
        if (c[i] % 2 == 0) {
            c[i] /= 2;
        } else {
            c[i + 1] += 26;
            c[i] /= 2;
        }
    }
}
void add() {
    for (int i = n; i >= 1; i--) {
        a[i] = (s[i] - 'a') + c[i];
        c[i - 1] += a[i] / 26;
        a[i] %= 26;
    }
}

int main() {
    scanf("%d%s%s", &n, s + 1, t + 1);
    sub();
    // for (int i = 1; i <= n; i++) cout << c[i] << ' '; puts("");
    div();
    // for (int i = 1; i <= n; i++) cout << c[i] << ' ';
    add();
    // for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    for (int i = 1; i <= n; i++) putchar(a[i] + 'a');
    return 0;
}