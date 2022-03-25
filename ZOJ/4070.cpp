#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;

int x, k, f[20] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &x, &k);
        int ans = x, i;
        for (i = 0; i < k; i++){
            int t = ans, sum = 0;
            if (t == 0) sum = 1;
            while (t){
                sum += f[t % 10]; t /= 10;
            }
            ans = sum;
            if (sum == 0) break;
        }
        if (i == k) printf("%d\n", ans);
        else printf("%d\n", (k - i + 1) % 2);
    }
    return 0;
}