#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, k, a[maxn];

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 1, tot = 0;
    for (int i = n; i >= 1; i--){
        if (tot + a[i] <= k){
            tot += a[i];
        }
        else {
            if (ans == m) return printf("%d", n - i), 0;
            ans++; tot = a[i];
        }
    }
    printf("%d", n);
    return 0;
}