#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;
const int maxv = 7000 + 10;

bitset<maxv> fac[maxv], mul[maxv], a[maxn];
int n, q;
int mu[maxv];

int main(){
    for (int i = 1; i < maxv; i++) mu[i] = 1;
    for (int i = 1; i < maxv; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % (j * j)) continue;
            mu[i] = 0; break;
        }
    }
    for (int i = 1; i < maxv; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j) continue;
            fac[i][j] = 1;
            mul[j][i] = mu[i / j];
        }
    }

    scanf("%d%d", &n, &q);
    int op, x, y, z;
    while (q--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            a[x] = fac[y];
        } else if (op == 2) {
            scanf("%d", &z);
            a[x] = a[y] ^ a[z];
        } else if (op == 3) {
            scanf("%d", &z);
            a[x] = a[y] & a[z];
        } else if (op == 4) {
            printf("%d", (a[x] & mul[y]).count() % 2);
        }
    }
    return 0;
}