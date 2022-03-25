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
const int maxn = 300000 + 5;

int n, cnt[26]; char s[maxn];

int main() {
    scanf("%d%s", &n, s);
    int ans = 0;
    for (int i = 0; i < 2 * n - 2; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            cnt[s[i] - 'a']++;
        } else {
            if (cnt[s[i] - 'A']) {
                cnt[s[i] - 'A']--;
            } else {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}