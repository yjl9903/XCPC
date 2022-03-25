#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const double eps = 1e-8;

int n, a[maxn], b[maxn];

bool check(double x){
    double l = -1e14, r = 1e14;
    for (int i = 0; i < n; i++){
        double d = 2.0 * x * b[i] - 1.0 * b[i] * b[i];
        if (d < eps) return 0;
        l = max(l, 1.0 * a[i] - sqrt(d)); r = min(r, 1.0 * a[i] + sqrt(d)); 
    }
    return r - l > eps;
}

int main(){
    scanf("%d", &n); 
    int flag = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", a + i, b + i);
        if (!flag){
            if (b[i] > 0) flag = 1;
            else if (b[i] < 0) flag = -1;
            else {
                if (cnt) return puts("-1"), 0;
                else cnt = 1;
            }
        }
        else {
            if (b[i] * flag < 0) return puts("-1"), 0;
        }
        b[i] = abs(b[i]);
    }
    double l = -1e14, r = 1e14;
    for (int i = 0; i < 100; i++){
        double m = (l + r) / 2;
        if (check(m)) r = m;
        else l = m;
    }
    printf("%.8lf", l);
    return 0;
}