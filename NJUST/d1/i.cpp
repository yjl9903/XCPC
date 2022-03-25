#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        int s = 0;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), s += a[i];
        if (s % 2){
            puts("no"); continue;
        }
        int flag = 1;
        for (int i = 0; i < n && flag; i++){
            sort(a, a + n, [](int a, int b){return a > b;});
            if (a[0] == 0) break;
            for (int j = 0; j < a[0]; j++){
                a[j + 1]--;
                if (a[j + 1] < 0) {
                    flag = 0; break;
                }
            }
            a[0] = 0;
        }
        if (flag) puts("yes");
        else puts("no");
    }
    return 0;
}