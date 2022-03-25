#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1000 + 5;

int l, r;
map<int,int> mp;

int main(){
    cin >> l >> r;
    if (r - l >= maxn) return puts("2"), 0;
    for (int i = l; i <= r; i++) {
        int x = i;
        for (int j = 1; j * j <= x; j++) {
            if (x % j) continue;
            if (j != 1) mp[j]++;
            if (j * j != x) mp[x / j]++;
        }
    }
    int ans = 0, mx = 0;
    for (auto& x: mp) {
        if (x.second > mx) {
            ans = x.first;
            mx = x.second;
        }
    }
    cout << ans << endl;
    return 0;
}