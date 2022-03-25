#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

double x[maxn][5];
int n;

int main(){
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 5; j++) scanf("%lf", &x[i][j]);
        }
        double ans = 0;
        int ss = 1 << 5;
        for (int s = 0; s < ss; s++){
            double ma = -1e200, mi = 1e200;
            for (int i = 0; i < n; i++){
                double t = 0;
                for (int j = 0; j < 5; j++){
                    if (s & (1 << j)) t += x[i][j];
                    else t -= x[i][j];
                }
                ma = max(t, ma); mi = min(t, mi);
            }
            ans = max(ans, ma - mi);
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}