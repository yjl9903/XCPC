#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

double ax, ay, bx, by;

int main(){
    while (cin >> ax >> ay >> bx >> by){
        double dx = ax - bx, dy = ay - by;
        double res = sqrt(dx * dx + dy * dy);
        printf("%.2f\n", res);
    }
    return 0;
}