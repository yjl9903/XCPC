#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int cal(vector<int> a) {
    int n = (int)a.size();
    vector<int> dp(n + 1, inf);
    int res = 0;
    for (int i = 0; i < n; i++) {
        int p = lower_bound(dp.begin() + 1, dp.begin() + res + 1, a[i]) - dp.begin();
        dp[p] = a[i];
        res = max(p, res);
    }
    return res;
}

int main() {
    int n; cin >> n;
    // vector<int> v;
    // for (int i = 1, x; i <= n; i++) cin >> x, v.push_back(x);
    // cout << cal(v);
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i + 1;
    int sum = 0, cnt = 0;
    // for (int t = 0; t < 10000; t++) {
    //     random_shuffle(p.begin(), p.end());
    //     sum += cal(p); cnt++;
    // }
    do {
        sum += cal(p); cnt++;
    } while (next_permutation(p.begin(), p.end()));
    printf("%d\n", sum);
    return 0;
}