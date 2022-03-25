#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];
int len, a[maxn], cnt;

ll cal(){
    ll sum = 0; s[len] = '9';
    int flag = s[0], x = 1;
    cnt = 0;
    for (int i = 1; i <= len; i++){
        if (flag == s[i]){
            x++;
        }
        else {
            flag = s[i];
            sum += 1ll * x * x;
            a[cnt++] = x;
            x = 1;
        }
    }
    return sum;
}

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> s; 
        len = strlen(s); ll res = cal(), ans = res, t = res;

        for (int i = 0; i < cnt; i++){
            if (a[i] == 1){
                int x = 1; t = res - 1;
                if (i - 1 >= 0) x += a[i - 1], t -= 1ll * a[i - 1] * a[i - 1];
                if (i + 1 < cnt) x += a[i + 1], t -= 1ll * a[i + 1] * a[i + 1];
                t += 1ll * x * x;
                // cout << i << ' ' << t << endl;
                ans = max(t, ans);
            }
        }

        for (int i = 0; i < cnt - 1; i++){
            if (a[i] == 1 || a[i + 1] == 1) continue;
            t = res - 1ll * a[i] * a[i] - 1ll * a[i + 1] * a[i + 1];
            t += 1ll * (a[i] - 1) * (a[i] - 1) + 1ll * (a[i + 1] + 1) * (a[i + 1] + 1);
            ans = max(t, ans);
            t = res - 1ll * a[i] * a[i] - 1ll * a[i + 1] * a[i + 1];
            t += 1ll * (a[i] + 1) * (a[i] + 1) + 1ll * (a[i + 1] - 1) * (a[i + 1] - 1);
            ans = max(t, ans);
        }

        cout << "Case #" << ++kase << ": " << ans << endl;
    }
    return 0;
}