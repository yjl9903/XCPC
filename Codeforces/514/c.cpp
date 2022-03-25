#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int n, a[maxn];

void dfs(int n, int base){
    if (n == 1){
        printf("%d", base);
    }
    if (n == 2){
        printf("%d %d", base, base * 2);
    }
    if (n == 3){
        printf("%d %d %d", base, base, base * 3);
    }
    if (n <= 3) return;
    for (int i = 1; i <= n; i += 2) printf("%d ", base);
    dfs(n / 2, base * 2);
}

int main(){
    scanf("%d", &n);
    if (n == 1) return puts("1"), 0;
    if (n == 2) return puts("1 2"), 0;
    if (n == 3) return puts("1 1 3"), 0;
    dfs(n, 1);
    return 0;
}