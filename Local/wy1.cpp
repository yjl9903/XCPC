#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    while (~scanf("%d", &n)){
        double ans = 0;
        for (int i = n; i >= 0; i--){
            double t = 1ll * double(50 + i) * double(50 + n - i) / 25;
            if (n - i > 50) break;
            ans = max(t, ans);
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}