#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int d;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &d);
        if (d * d >= 4 * d){
            double dt = d * d - 4 * d;
            dt = sqrt(dt);
            printf("Y %.10lf %.10lf\n", (d + dt) / 2, (d - dt) / 2);
        }  
        else puts("N"); 
    }
    return 0;
}