#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <deque>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    deque<ll> dq;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), dq.push_back(a[i]);
    int ans = 0;
    while (!dq.empty()) {
        if ((int)dq.size() == 1) break;
        if (dq.front() == dq.back()) {
            dq.pop_back(); dq.pop_front(); continue;
        }
        if (dq.front() < dq.back()) {
            ll x = dq.front(); dq.pop_front();
            ll y = dq.front(); dq.pop_front();
            dq.push_front(x + y); ans++;
        } else {
            ll x = dq.back(); dq.pop_back();
            ll y = dq.back(); dq.pop_back();
            dq.push_back(x + y); ans++;
        }
    }
    cout << ans << endl;
    return 0;
}