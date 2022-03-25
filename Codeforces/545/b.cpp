#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n; char c[maxn], a[maxn];

int c1, c2, c3, c4;
int check(int x, int y) {
    if (y - x + c4 < 0) return 0;
    if ((y - x + c4) % 2) return 0;
    
    int k = (y - x + c4) / 2;
    int a2 = x, a3 = c3 - y, a4 = k, a1 = n / 2 - a2 - a3 - a4;

    if (k > c4) return 0;
    if (a1 < 0 || a1 > c1) return 0;

    for (int i = 1; i <= n; i++) {
        if (c[i] == '0' && a[i] == '0') {
            if (a1) printf("%d ", i), a1--;
        }
        if (c[i] == '1' && a[i] == '0') {
            if (a2) printf("%d ", i), a2--;
        }
        if (c[i] == '0' && a[i] == '1') {
            if (a3) printf("%d ", i), a3--;
        }
        if (c[i] == '1' && a[i] == '1') {
            if (a4) printf("%d ", i), a4--;
        }
    }
    return 1;
}

int main() {
    scanf("%d%s%s", &n, c + 1, a + 1);
    for (int i = 1; i <= n; i++) {
        if (c[i] == '0' && a[i] == '0') c1++;
        if (c[i] == '1' && a[i] == '0') c2++;
        if (c[i] == '0' && a[i] == '1') c3++;
        if (c[i] == '1' && a[i] == '1') c4++;
    }
    for (int i = 0; i <= c2; i++) for (int j = 0; j <= c3; j++) if (check(i, j)) return 0;
    puts("-1");
    return 0;
}