#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        int ans = 0;   
        for (int i = 0, x, y; i < n; i++){
            scanf("%d%d", &x, &y);
            ans += x * y;
        }
        printf("%d\n", ans);
    }
    return 0;
}