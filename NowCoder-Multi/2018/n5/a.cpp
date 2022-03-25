#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;
const double eps = 1e-7;

int n, k, s[maxn], c[maxn];
double d[maxn];

int getInt(){
    char ch = getchar(); int x = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

bool cal(double x){
    for (int i = 0; i < n; i++) d[i] = 1.0 * s[i] * c[i] - x * s[i];
    sort(d, d + n);
    double ans = 0;
    for (int i = k; i < n; i++) ans += d[i];
    return ans > 0;
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &s[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    double l = 1, r = 1000;
    while (r - l > eps){
        double m = (l + r) / 2;
        if (cal(m)){
            l = m;
        }
        else {
            r = m;
        }
    }
    printf("%.6lf\n", l);
    return 0;
}