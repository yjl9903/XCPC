#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;

int n, a[maxn] = {0}, vis[maxn] = {0};

int main(){
    scanf("%d", &n);
    int ss = 0, t = n, k = 0;
    while (t){
        t /= 2;
        ss = ss * 2 + 1;
        k++;
    }
    if (n % 2){
        a[0] = 0; vis[0] = 1;
    }
    else {
        a[0] = n - 1; vis[0] = 1;
    }
    for (int i = 0; i < n; i++){
        if (vis[i]) continue;
        int t = (~i) & ss, c = 1;
        while (t >= n || vis[t]){
            t = t & (ss >> c);
            c++;
            // if (t == 0) break;
        }
        // printf("%d: %x\n", i, t);
        vis[t] = vis[i] = 1;
        a[i] = t; a[t] = i;
    }
    printf("%d", a[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", a[i]);
    }
    return 0;
}