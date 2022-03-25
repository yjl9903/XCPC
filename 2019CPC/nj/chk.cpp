#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;



int main() {
    double two = 1, sum = 0;
    for (int i = 1; i <= 100; i++) {
        two *= 2.0;
        cout << 1.0 * i * (i + 1) / 2.0 / two << endl;
        sum += 1.0 * i * (i + 1) / 2.0 / two;
    }
    printf("%.2lf", sum);
    return 0;
}