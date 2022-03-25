#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100 + 5;

int n, sum = 0; char s[maxn];

map<PII,int> mp;
int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int dfs(int pos, int cnt) {
    if (cnt + n - pos > sum) return -1000000;
    if (pos == n) {
        if (cnt == sum) return 0;
        else return -1000000;
    }
    if (mp.count({ pos, cnt })) return mp[{pos, cnt}];
    int mx = -1000000;
    for (int i = 0; i <= 9; i++) {
        // if (i == 2 || i == 3 || i == 6) continue;
        mx = max(mx, i + dfs(pos + 2, cnt + c[i] + 2));
    }
    for (int i = 0; i <= 9; i++) {
        // if (i == 9 || i == 5 || i == 3) continue;
        mx = max(mx, -i + dfs(pos + 2, cnt + c[i] + 1));
    }
    return mp[{pos, cnt}] = mx;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        sum = 0; mp.clear();
        scanf("%d%s", &n, s);   
        for (int i = 0; i < n; i++) {
            if (s[i] == '+') sum += 2;
            else if (s[i] == '-') sum++;
            else sum += c[s[i] - '0'];
        }
        int ans = s[0] - '0';
        for (int i = 1; i < n; i += 2) {
            if (s[i] == '+') ans += s[i + 1] - '0';
            else ans -= s[i + 1] - '0';
        }
        for (int i = 0; i <= 9; i++) {
            ans = max(ans, i + dfs(1, c[i]));
        }
        printf("%d\n", ans);
    }
    return 0;
}