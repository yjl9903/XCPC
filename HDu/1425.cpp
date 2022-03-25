#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int a[maxn], n, m;

int main(){
    while (~scanf("%d%d", &n, &m)){
        for (int i = 0; i < n; scanf("%d", &a[i++]));
        sort(a, a + n, greater<int>());
        for (int i = 0; i < m; i++){
            if (i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
    }
    return 0;
}