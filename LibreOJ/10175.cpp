#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, k, a[maxn];

int q[maxn], ans[maxn];
void getmin(){
    int l = 0, r = 0;
    for (int i = 1; i < k; i++){
        while (l <= r && a[q[r]] >= a[i]) r--;
        q[++r] = i;
    }
    for (int i = k; i <= n; i++){
        while (l <= r && a[q[r]] >= a[i]) r--;
        q[++r] = i;
        while (i - q[l] >= k) l++;
        ans[i] = a[q[l]];
    }
}
void getmax(){
    int l = 0, r = 0;
    for (int i = 1; i < k; i++){
        while (l <= r && a[q[r]] <= a[i]) r--;
        q[++r] = i;
    }
    for (int i = k; i <= n; i++){
        while (l <= r && a[q[r]] <= a[i]) r--;
        q[++r] = i;
        while (i - q[l] >= k) l++;
        ans[i] = a[q[l]];
    }
}

int main(){
    scanf("%d%d", &n, &k); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    getmin(); for (int i = k; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    getmax(); for (int i = k; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}