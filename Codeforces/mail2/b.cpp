#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, l, a[maxn];

int main(){
    scanf("%d%d%d", &n, &m, &l);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);

    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++){
        if (a[i] > l) cnt++;
        else {
            if (cnt) ans++;
            cnt = 0;
        }
    }
    if (cnt) ans++;

    int op, p, d;
    while (m--){
        scanf("%d", &op);
        if (op == 0){
            printf("%d\n", ans);
        }
        else if (op == 1){
            scanf("%d%d", &p, &d);
            if (a[p] <= l){
                a[p] += d;
                if (a[p] <= l) continue;
                if (p - 1 >= 1 && p + 1 <= n && a[p + 1] > l && a[p - 1] > l){
                    ans--;
                }
                else if (p - 1 >= 1 && p + 1 <= n && a[p + 1] <= l && a[p - 1] <= l){
                    ans++;
                }
                if (p == 1 && p + 1 <= n && a[p + 1] <= l){
                    ans++;
                }
                if (p == n && p - 1 >= 1 && a[p - 1] <= l){
                    ans++;
                }
                if (n == 1) ans++;
            }
        }
    }
    return 0;
}