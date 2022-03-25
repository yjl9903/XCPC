#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    int d1 = a[n - 2] - a[0], d2 = a[n - 1] - a[1];
    cout << min(d1, d2);
    return 0;
}