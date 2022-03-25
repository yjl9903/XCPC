#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, a[maxn], dp[maxn];

int main(){
    while (cin >> n && n){
        for (int i = 0; i < n; i++) cin >> a[i];
        cin >> m;
        if (m < 5){
            cout << m << endl; continue;
        }
        sort(a, a + n);
        m -= 5;
        ms(dp, 0);
        for (int i = 0; i < n - 1; i++) for (int j = m; j >= a[i]; j--){
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
        }
        cout << 5 - a[n - 1] + m - dp[m] << endl;
    }
    return 0;
}