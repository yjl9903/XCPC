#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

double x;

int main(){
    while (cin >> x){
        if (x < 0) x = -x;
        printf("%.2f\n", x);
    }
    return 0;
}