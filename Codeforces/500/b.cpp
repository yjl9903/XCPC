#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, x, a[maxn], vis[maxn] = {0}, vis2[maxn] = {0};

int main(){
    scanf("%d%d", &n, &x);
    int flag = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (vis[a[i]]) flag = 1;
        vis[a[i]] = 1;
    }
    if (flag) {
        puts("0"); return 0;
    }
    for (int i = 0; i < n; i++){
        if ((a[i] & x) != a[i]){
            if (vis[a[i] & x]) {
                flag = 1; break;
            }
        }
    }
    if (flag){
        puts("1"); return 0;
    }
    for (int i = 0; i < n; i++){
        if (vis2[a[i] & x]) flag = 1;
        vis2[a[i] & x] = 1;
    }
    if (flag) puts("2");
    else puts("-1");
    return 0;
}