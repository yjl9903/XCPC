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
    if (a[0] != 0) return puts("1"), 0;
    int m = 0;
    for (int i = 1; i < n; i++){
        if (a[i] > m + 1){
            printf("%d", i + 1); return 0;
        }
        m = max(a[i], m);
    }
    puts("-1");
    return 0;
}