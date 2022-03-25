#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;

int main(){
    while (~scanf("%d%d", &n, &m)){
        double x = n, res = 0;
        while (m--){
            res += x;
            x = sqrt(x);
        }
        printf("%.2f\n", res);
    }
    return 0;
}