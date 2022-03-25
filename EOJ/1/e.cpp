#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int a[10];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        double ans = 0;
        ll sum = 0;
        for (int i = 1, x; i <= 6; i++) {
            scanf("%d", &x);
            sum += x;
            ans = max(1.0 * i * x, ans);
        }
        printf("%.12lf\n", ans / sum);
    }
    return 0;
}