#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

char s[maxn];
int n;

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    int l = 1, r = n;
    string ans;
    while (r - l >= 3) {
        if (s[l] == s[r]) {
            ans += s[l]; l++; r--;
        } else if (s[l] == s[r - 1]) {
            ans += s[l]; l++; r -= 2;
        } else if (s[l + 1] == s[r]) {
            ans += s[r]; l += 2; r--;
        } else if (s[l + 1] == s[r - 1]) {
            ans += s[l + 1]; l += 2; r -= 2;
        }
    }
    string res = ans; reverse(res.begin(), res.end());
    if (l <= r) ans += s[l];
    cout << ans << res;
    return 0;
}