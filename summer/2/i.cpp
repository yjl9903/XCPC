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
const int maxn = 100000 + 5;

int n, a[maxn];

double cal(int a, int b, int c) {
    if (a + b <= c || a + c <= b || b + c <= a) return 0;
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
double ans;
double dfs(int p) {
    
}

int main() {
    while (scanf("%d", &n) == 1) {
        if (n == 0) break; 
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ans = 0;

        printf("%.2lf\n", ans);
    }
    return 0;
}