#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m, pre[maxn];
unordered_map< int,vector<int> > mp;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, s, r; i <= n; i++) {
        scanf("%d%d", &s, &r);
        mp[s].push_back(r);
    }
    for (auto& x: mp) sort(x.second.begin(), x.second.end(), greater<int>());
    int ans = 0;
    for (int len = 1; len <= n; len++) {
        int tot = 0;
        unordered_map< int,vector<int> > nmp;
        vector<int> v;
        for (auto& x: mp) {
            if ((int)x.second.size() < len) {
                v.push_back(x.first); continue;
            }
            pre[x.first] += x.second[len - 1];
            if (pre[x.first] > 0) tot += pre[x.first];
        }
        for (int& x: v) mp.erase(x);
        ans = max(ans, tot);
    }
    cout << ans << endl;
    return 0;
}