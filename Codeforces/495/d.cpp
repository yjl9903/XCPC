#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int cnt = 0, a[maxn], sum[maxn] = {0}, mmax = 0;
int sum2[maxn];

bool check(int n, int m, int x, int y){
    ms(sum2, 0);
    // cout << n << ' ' << m << endl << x << ' ' << y;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int now = abs(i - x) + abs(j - y);
            sum2[now]++;
            if (sum2[now] > sum[now])
                return 0;
        }
    }
    cout << n << ' ' << m << endl << x << ' ' << y;
    return 1;
}
bool solve(int n, int m, int t){
    // cout << n << ' ' << m << ' ' << t << endl;
    int x = t, y = n + m - x - mmax;
    return check(n, m, x, y) || check(n, m, y, x);
}

int main(){
    cin >> cnt;
    for (int i = 0; i < cnt; cin >> a[i++]);
    for (int i = 0; i < cnt; i++) sum[a[i]]++, mmax = max(mmax, a[i]);
    if (sum[0] != 1){
        cout << -1; return 0;
    }
    int t = 1;
    for (int i = 1; i < cnt; i++) if (sum[i] != 4 * i){
        t = i; break;
    }

    for (int i = 1; i * i <= cnt; i++){
        if (cnt % i) continue;
        if (solve(i, cnt / i, t)){
            return 0;
        }
    }
    cout << -1;
    return 0;
}