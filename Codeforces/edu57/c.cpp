#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int ang;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &ang);
        int ans = -1;
        for (int i = 3; i <= 1000; i++) if (i * ang % 180 == 0) {
            int k = i * ang / 180;
            if (k <= i - 2) {
                ans = i; break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}