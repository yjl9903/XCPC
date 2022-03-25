#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, cnt[300]; char s[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) cnt[s[i]]++;
    int sum = 0; for (int i = 1; i <= 150; i++) if (cnt[i]) sum++;
    map<char,int> mp;
    int l = 1, ans = 1e9;
    for (int i = 1; i <= n; i++) {
        mp[s[i]]++;
        while (l < i && (int)mp.size() == sum && mp[s[l]] > 1) {
            mp[s[l]]--; if (mp[s[l]] == 0) mp.erase(s[l]);
            l++;
        }
        if ((int)mp.size() == sum) ans = min(ans, i - l + 1);
    }
    cout << ans << endl;
    return 0;
}