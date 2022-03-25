#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn], vis[maxn];

int main(){
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int tp = 1;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        if (vis[x]) {
            printf("0 "); continue;
        }
        int cnt = 0;
        while (tp <= n && a[tp] != x) vis[a[tp++]] = 1, cnt++;
        if (tp <= n && a[tp] == x) tp++, vis[x] = 1, cnt++; 
        printf("%d ", cnt);
    }
    return 0;
}