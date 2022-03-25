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
const int maxn = 10000000 + 5;

int n, vis[maxn];

int cal(int n) {
    ms(vis, 0);
    for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) for (int k = 0; k <= n; k++) {
        if (i + j + k > n) break;
        vis[i + 5 * j + 10 * k + 50 * (n - i - j - k)] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= 50 * n; i++) if (vis[i]) ans++;
    return ans;
}

int ans[] = {0,4,10,20,35,56,83,116,155,198,244,292,341,390,439,488,537,586,635,684,733,782,831,880,929,978,1027,1076,1125,1174,1223,1272,1321,1370,1419,1468,1517,1566,1615,1664,1713,1762,1811,1860,1909,1958,2007,2056,2105,2154,2203,2252,2301,2350,2399,2448,2497,2546,2595,2644,2693,2742,2791,2840,2889,2938,2987,3036,3085,3134,3183,3232,3281,3330,3379,3428,3477,3526,3575,3624,3673,3722,3771,3820,3869,3918,3967,4016,4065,4114,4163,4212,4261,4310,4359,4408,4457,4506,4555,4604,4653};

int main() {
    // for (int i = 1; i <= 100; i++) cout << cal(i) << ',';
    cin >> n;
    if (n <= 100) cout << ans[n] << endl;
    else cout << 49ll * (n - 100) + ans[100] << endl;
    // cout << cal(n) << endl; 
    return 0;
}