#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, k, a[maxn];
char s[maxn];

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%s", s + 1);
    ll ans = 0;
    int i = 1;
    while (i <= n) {
        int j = i;
        vector<int> v;
        while (j <= n && s[j] == s[i]) v.push_back(a[j++]);
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        for (int i = 0; i < min((int)v.size(), k); i++) ans += v[i];
        // cout << ans << endl;
        i = j;
    }
    cout << ans << endl;
    return 0;
}