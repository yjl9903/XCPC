#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;
const int maxv = 250000 + 5;
const int inf = 1 << 30;

int n, v[maxn], m[maxn], dp[maxv], head, tail, head2, tail2;
// PII dq[maxv];
int dq[maxv], dq2[maxv];

int main(){
    while (cin >> n && n > 0){
        int s = 0;
        for (int i = 0; i < n; i++) cin >> v[i] >> m[i], s += v[i] * m[i];
        int w = s / 2;
        ms(dp, 0);
        // fill(dp, dp + maxv, inf); dp[0] = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < v[i]; j++){
                head = 1, tail = 0; head2 = 1, tail2 = 0;
                for (int k = j, cnt = 0; k <= w; k += v[i], cnt++){
                    if (tail2 - head2 == m[i]){
                        if (dq2[head2] == dq[head]) head++;
                        head2++;
                    }
                    int t = dp[k] - cnt * v[i];
                    dq2[++tail2] = t;
                    while (head <= tail && dq2[tail] < t) tail--;
                    dq[++tail] = t;
                    dp[k] = dq[head] + cnt * v[i];
                }
            }
        }
        int a = 0;
        for (int i = w; i >= 1; i--) if (dp[i]) {
            a = dp[i]; break;
        }
        cout << s - a << ' ' << a << endl;
    }
    return 0;
}