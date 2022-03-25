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

int a[3], b[3];
ll ans[3][2];

int get(int x, int i) {
    return x * x + a[i] * x + b[i];
}

int cal(int x1, int y1) {

}

int main(){
    for (int i = 0; i < 3; i++) scanf("%d%d", a + i, b + i);

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (a[i] % 2 == a[j] % 2 && a[i] % 2 == 0) {
                int d = b[j] - b[i] + (a[j] * a[j] - a[i] * a[i]) / 4;
                
            }
        }
    }
    return 0;
}