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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a[maxn], cnt[maxn];

int main() {
    for (int i = 1; i <= 18; i++) cin >> a[i], cnt[a[i]]++;
    for (int i = 1; i <= 13; i++) {
        if (cnt[i] >= 2) cnt[i] -= 2;
        if (cnt[i] >= 2) cnt[i] -= 2;
    }
    int ans = 0;
    for (int i = 0; i <= 13; i++) ans += cnt[i];
    cout << ans;
    return 0;
}