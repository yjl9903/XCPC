#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 0, cnt = 1, flag = 0, f = 0, sum = 0;
    if (a[1] == 1) flag = 1;
    for (int i = 2; i <= n; i++){
        if (a[i] == a[i - 1] + 1){
            cnt++;
        }
        else {
            if (flag && cnt > 1) ans += cnt - 1;
            else if (cnt > 2) ans += cnt - 2;
            cnt = 1; flag = 0; sum++;
        }
    }
    if (a[n] == 1000 && cnt > 1) ans += cnt - 1;
    else if (flag && cnt > 1) ans += cnt - 1;
    else if (cnt > 2) ans += cnt - 2;
    cout << ans << endl;
    return 0;
}