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
const int maxn = 100000 + 5;

int n; char s[maxn];

int main() {
    cin >> n >> s + 1;
    int c = 0;
    for (int i = 1; i <= n; i++) if (s[i] == 'G') c++;
    int last = -1, len = 0, ans = 0, tot = 0, l = -1, r = -1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'G') {
            if (l == -1) l = i;
            tot++; r = i;
            ans = max(ans, tot);
            if (last != -1) {
                if (last + 2 == l && len + tot + 1 <= c) {
                    ans = max(ans, len + tot + 1);
                }
            }
        } else {
            if (tot + 1 <= c) ans = max(ans, tot + 1);
            len = tot; 
            last = r;
            l = r = -1;
            tot = 0;
        }
    }
    if (tot + 1 <= c) ans = max(ans, tot + 1);
    cout << ans << endl;
    return 0;
}