#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;

int n, a[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int res = 1 << 30;
        for (int i = 0; i < n; i++){
            int t = 0;
            for (int j = 0; j < n; j++) t += abs(a[i] - a[j]);
            res = min(t, res);
        }
        cout << res << endl;
    }
    return 0;
}