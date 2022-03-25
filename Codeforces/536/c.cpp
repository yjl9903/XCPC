#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 300000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    ll sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        ll t = a[i] + a[n - i + 1];
        sum += t * t;
    }
    cout << sum << endl;
    return 0;
}