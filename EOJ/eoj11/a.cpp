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
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        printf("Case #%d: 0 0 0 0 %d 1000000\n", ++kase, n);
    }
    return 0;
}