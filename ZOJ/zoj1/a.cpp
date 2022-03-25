#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

ll n, two[100];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld", &n);
        n--; int cnt = 0;
        for (int i = 0; i < 63; i++) if ((1ll << i) & n) cnt++;
        printf("%lld\n", 1ll << cnt);
    }
    return 0;
}