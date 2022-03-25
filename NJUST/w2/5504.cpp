#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll a[maxn], b[maxn];
int n;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n;
        for (int i = 0; i < n; cin >> a[i++]);
        sort(a, a + n);
        ll res = 1, m = a[0];
        int cnt = 0, flag = 0;
        for (int i = 0; i < n; i++){
            m = max(m , a[i]);
            if (a[i] < 0){
                b[cnt++] = a[i];
            }
            else if (a[i] > 0){
                res *= a[i]; flag = 1;
            }
        }
        for (int i = 0; i < cnt - 1; i++) res *= b[i], flag = 1;
        if (res < 0) res *= b[cnt - 1], flag = 1;

        if (flag) cout << res << endl;
        else cout << m << endl;
    }
    return 0;
}