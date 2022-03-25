#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, l, a, s[maxn], len[maxn];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> l >> a;
    int ans = 0, tot = 0;
    for (int i = 0; i < n; i++){
        cin >> s[i] >> len[i];
    }
    s[n] = l;
    while (tot + a <= s[0]) ans++, tot += a;
    for (int i = 0; i < n; i++){
        tot = s[i] + len[i];
        while (tot + a <= s[i + 1]) ans++, tot += a;
    }
    while (tot + a <= l) ans++, tot += a;
    cout << ans;
    return 0;
}