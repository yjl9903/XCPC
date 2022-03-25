#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll l, r;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%I64d%I64d", &l, &r);
        printf("%I64d %I64d\n", 1ll * l, 2ll * l);
    }
    return 0;
}