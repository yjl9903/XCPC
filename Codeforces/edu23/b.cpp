#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    if (a[0] == a[1] && a[1] == a[2]){
        int i = 0; while (i < n && a[i] == a[0]) i++;
        printf("%I64d\n", 1ll * i * (i - 1) * (i - 2) / 6);
    }
    else if (a[1] == a[2]){
        int i = 1; while (i < n && a[i] == a[1]) i++;
        printf("%I64d", 1ll * (i - 1) * (i - 2) / 2);
    }
    else{
        int i = 2; while (i < n && a[i] == a[2]) i++;
        printf("%d\n", i - 2);
    }
    return 0;
}