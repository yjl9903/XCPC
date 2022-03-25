#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

int cash, n, dp[maxn], v[maxn], m[maxn];
// PII dq[maxn];
vector<int> val;

int main(){
    ios::sync_with_stdio(false);
    while (cin >> cash >> n){
        val.clear();
        for (int i = 0; i < n; i++){
            cin >> m[i] >> v[i];
            for (int b = 1; b < m[i]; b <<= 1){
                val.push_back(v[i] * b);
                m[i] -= b;
            }
            val.push_back(v[i] * m[i]);
        }
        ms(dp, 0);
        for (int i = 0; i < val.size(); i++){
            for (int j = cash; j >= val[i]; j--){
                dp[j] = max(dp[j], dp[j - val[i]] + val[i]);
            }
        }
        cout << dp[cash] << endl;
    }
    return 0;
}