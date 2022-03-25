#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn], cnt[maxn], nxt[maxn];
map<int,int> mp;

int main(){
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i), mp[a[i]]++;
    int mx = 0;
    for (auto& x : mp) cnt[x.second]++, mx = max(x.second, mx);
    nxt[maxn + 1] = -1;
    for (int i = maxn; i >= 0; i--){
        if (cnt[i]) nxt[i] = i;
        else nxt[i] = nxt[i + 1];
    }
    // for (int i = maxn; i >= 0; i--) cnt[i] += cnt[i + 1];

    // for (int i = 1; i <= 10; i++) cout << cnt[i] << ' '; cout << endl;
    // for (int i = 1; i <= 10; i++) cout << nxt[i] << ' '; cout << endl;

    ll ans = 0;
    for (int c = 1; c <= mx; c++){
        int last = c, tot = 0;
        vector<int> v;
        while (last < maxn && nxt[last] != -1){
            int now = nxt[last];
            // if (cnt[now] == 0) break;
            while (now != -1 && cnt[now] == 0) now = nxt[now + 1];
            if (now == -1) break; 
            v.push_back(now); cnt[now]--;
            // while (nxt[last] != -1 && cnt[nxt[last]] == 0) nxt[last] = nxt[nxt[last] + 1];
            last += last; tot++;
        }
        // cout << c << ' ' << tot << endl;
        ans = max(ans, 1ll * c * ((1 << tot) - 1));
        for (int x : v) cnt[x]++;
    }
    cout << ans << endl;
    return 0;
}