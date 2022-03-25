#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

double res[maxn];
int n;

int main(){
    res[0] = 0;
    for (int i = 1; i < maxn; i++){
        if (i % 2) res[i] = res[i - 1] + 1.0 / double(i);
        else res[i] = res[i - 1] - 1.0 / double(i);
    }
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        printf("%.2f\n", res[n]);
    }
    return 0;
}