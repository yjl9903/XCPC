#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

string a, b;
int cnt[10];

int main() {
    cin >> a >> b;
    if (a.length() < b.length()) {
        sort(a.begin(), a.end()); reverse(a.begin(), a.end());
        cout << a << endl; return 0;
    }
    ll y = 0; for (int i = 0; i < b.length(); i++) y = y * 10 + (b[i] - '0');
    for (int i = 0; i < a.length(); i++) cnt[a[i] - '0']++;

    ll ans = -1;
    int sum[10]; ms(sum, 0);
    string tmp;
    for (int i = b[0] - '0' - 1; i >= 0; i--) if (cnt[i]) {
        tmp += (i + '0'); sum[i]++; break;
    }
    if ((int)tmp.length() == 1) {
        for (int i = 9; i >= 0; i--) while (cnt[i] - sum[i] > 0) tmp += (i + '0'), sum[i]++;
        ans = 0;
        for (int i = 0; i < tmp.length(); i++) ans = ans * 10ll + (tmp[i] - '0');
    }

    for (int i = 0; i < b.length() - 1; i++) {
        ms(sum, 0);
        for (int j = 0; j <= i; j++) sum[b[j] - '0']++;
        int flag = 0;
        for (int j = 0; j < 10; j++) if (cnt[j] < sum[j]) { flag = 1; break; }
        if (flag) continue;
        string tmp;
        for (int j = 0; j <= i; j++) tmp += b[j];
        for (int j = b[i + 1] - '0' - 1; j >= 0; j--) if (cnt[j] - sum[j] > 0) {
            tmp += (j + '0'); sum[j]++; break;
        }
        for (int j = 9; j >= 0; j--) while (cnt[j] - sum[j] > 0) tmp += (j + '0'), sum[j]++;
        ll r = 0;
        for (int j = 0; j < tmp.length(); j++) r = r * 10 + (tmp[j] - '0');
        if (r <= y) ans = max(r, ans);
    }
    if (ans == -1) cout << a << endl;
    else cout << ans << endl;
    return 0;
}