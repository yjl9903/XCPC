#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, a[maxn], que[maxn], id[maxn], lt[maxn], rt[maxn];

ll cal1(){
    int r = 0, l = 1; que[0] = 1 << 30; id[0] = 0;
    for (int i = 1; i <= n; i++){
        while (1 <= r && que[r] <= a[i]) r--;
        lt[i] = i - id[r] - 1;
        que[++r] = a[i]; id[r] = i;
    }
    l = n + 1; r = n; que[n + 1] = 1 << 30; id[n + 1] = n + 1;
    for (int i = n; i >= 1; i--){
        while (l <= n && que[l] < a[i]) l++;
        rt[i] = id[l] - i - 1;
        que[--l] = a[i]; id[l] = i;
    }
    ll ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     cout << lt[i] << ' ' << rt[i] << endl;
    // }
    for (int i = 1; i <= n; i++) ans += 1ll * a[i] * (lt[i] + 1) * (rt[i] + 1);
    return ans;
}
ll cal2(){
    int r = 0, l = 1; que[0] = 1 << 30; id[0] = 0;
    for (int i = 1; i <= n; i++){
        while (1 <= r && que[r] >= a[i]) r--;
        lt[i] = i - id[r] - 1;
        que[++r] = a[i]; id[r] = i;
    }
    l = n + 1; r = n; que[n + 1] = 1 << 30; id[n + 1] = n + 1;
    for (int i = n; i >= 1; i--){
        while (l <= n && que[l] > a[i]) l++;
        rt[i] = id[l] - i - 1;
        que[--l] = a[i]; id[l] = i;
    }
    ll ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     cout << lt[i] << ' ' << rt[i] << endl;
    // }
    for (int i = 1; i <= n; i++) ans += 1ll * a[i] * (lt[i] + 1) * (rt[i] + 1);
    return ans;
}

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    // cout << cal1() << endl;
    // cout << endl;
    // cout << cal2() << endl;
    cout << cal1() - cal2() << endl;
    return 0;
}