#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

ll k; int x;

int cal(int x) {
    if (x <= 9) return x;
    int sum = 0;
    while (x) {
        sum += x % 10; x /= 10;
    }
    return cal(sum);
}

int main(){
    // for (int i = 1; i <= 200; i++) cout << cal(i) << endl;
    int T; scanf("%d", &T);
    while (T--){
        scanf("%I64d%d", &k, &x);
        printf("%I64d\n", x + (k - 1) * 9ll);
    }
    return 0;
}