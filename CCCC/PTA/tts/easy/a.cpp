#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, m;
map<string,int> mp, mp2;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        string s;
        if (k == 1) {
            cin >> s; continue;
        }
        while (k--) {
            cin >> s;
            mp[s] = 1;
        }
    }
    cin >> m;
    string s; int flag = 0;
    while (m--) {
        cin >> s;
        if (mp.count(s) || mp2.count(s)) continue;
        if (flag) cout << ' ';
        cout << s; flag = 1;
        mp2[s] = 1;
    }
    if (!flag) puts("No one is handsome");
    return 0;
}