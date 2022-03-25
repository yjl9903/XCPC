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
const int maxn = 100000 + 5;

int a[200][200], b[200][200], c[200][200];
int r1, c1, r2, c2;

int main() {
    scanf("%d%d", &r1, &c1);
    for (int i = 0; i < r1; i++) for (int j = 0; j < c1; j++) scanf("%d", &a[i][j]);
    scanf("%d%d", &r2, &c2);
    for (int i = 0; i < r2; i++) for (int j = 0; j < c2; j++) scanf("%d", &b[i][j]);
    if (c1 != r2) return printf("Error: %d != %d", c1, r2), 0;
    for (int i = 0; i < r1; i++) for (int j = 0; j < c2; j++) {
        for (int k = 0; k < c1; k++) {
            c[i][j] += a[i][k] * b[k][j];
        }
    }
    printf("%d %d\n", r1, c2);
    for (int i = 0; i < r1; i++) for (int j = 0; j < c2; j++) printf("%d%c", c[i][j], " \n"[j == c2 - 1]);
    return 0;
}