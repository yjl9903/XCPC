#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 50 + 5;
const int maxv = 250000 + 5;
const int inf = 1 << 30;

int n, v[maxn], m[maxn], dp[maxv], head, tail;
PII dq[maxv];

int main(){
    while (cin >> n && n > 0){
        int s = 0;
        for (int i = 0; i < n; i++) cin >> v[i] >> m[i], s += v[i] * m[i];
        int w = s / 2;
        // ms(dp, 0);
        fill(dp, dp + maxv, inf); dp[0] = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < v[i]; j++){
                head = 1; tail = 0;
                dq[++tail] = make_pair(dp[j], j);
                for (int k = j + v[i], t = 1; k <= w; k += v[i], t++){
                    while (head <= tail && (t - dq[head].second) > m[i] * v[i]) head++;
                    while (head <= tail && dq[head].first + (t - dq[head].second) / v[i] < dq[tail].first) tail--;
                    dq[++tail] = make_pair(dp[k], k);
                    dp[k] = min(dp[k], dq[head].first + (k - dq[head].second) / v[i]);
                }
            }
        }
        int a = 0;
        for (int i = w; i >= 0; i--) if (dp[i] != inf) {
            a = i; break;
        }
        cout << s - a << ' ' << a << endl;
    }
    return 0;
}