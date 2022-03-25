#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define PI 3.1415927
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

double r;

int main(){
    while (cin >> r){
        double res = 4.0 / 3.0 * PI * r * r * r;
        printf("%.3f\n", res);
    }
    return 0;
}