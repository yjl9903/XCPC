#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <deque>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, a[maxn], pre[maxn]; map<int,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mp[a[i]]++;
    // sort(a + 1, a + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int tot = 0;
        for (int j = a[i]; j <= a[i] + 5; j++) tot += mp[j];
        ans = max(ans, tot);
    }
    cout << ans << endl;
    // int tot = 0, ans = 1;
    // deque<int> v;
    // for (auto& x: mp) {
    //     while (!v.empty() && v.front() < x.first - 5) {
    //         tot -= mp[v.front()]; v.pop_front();
    //     }
    //     while ((int)v.size() >= 5) {
    //         tot -= mp[v.front()]; v.pop_front();
    //     }
    //     v.push_back(x.first);
    //     assert((int)v.size() <= 5);
    //     tot += x.second;
    //     ans = max(ans, tot);
    // }
    // cout << ans << endl;
    return 0;
} 