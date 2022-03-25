#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, sum[maxn]; char s[maxn], t[3], d[3];
map< int,set<int> > mp;

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 1; i <= n; i++) {
        mp[s[i] - 'A'].insert(i);
        sum[i] = 1;
    }
    for (int i = 1; i <= q; i++) {
        scanf("%s%s", t, d);
        int op = 1; if (d[0] == 'L') op = -1;
        set<int> st;
        for (auto& x: mp[t[0] - 'A']) {
            if (x + op > n || x + op < 1) {
                sum[x] = 0; continue;
            }
            sum[x + op] += sum[x]; sum[x] = 0;
            if (s[x + op] == t[0]) st.insert(x + op);
            else mp[s[x + op] - 'A'].insert(x + op);
        }
        mp[t[0] - 'A'] = st;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += sum[i];
    cout << ans << endl;
    return 0;
}