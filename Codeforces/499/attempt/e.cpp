#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, k, a[maxn];
int dp[maxn] = {0};
vector<int> v;

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i] %= k;
    sort(a, a + n); n = unique(a, a + n) - a;
    for (int i = 0; i < n; i++){
        dp[a[i]] = 1;
        for (int j = a[i]; j < 2 * k; j++){
            if (dp[(j - a[i]) % k]) dp[j % k] = 1;
        }
        // if (dp[k - a[i]]) dp[0] = 1;
    }
    for (int i = 0; i < k; i++) if (dp[i]) v.push_back(i);
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); i++){
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}