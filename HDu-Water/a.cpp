#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        sort(a, a + n);
        int res = -1;
        for (int i = n - 3; i >= 0; i--){
            if (a[i] + a[i + 1] > a[i + 2]){
                res = a[i] + a[i + 1] + a[i + 2];
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}