#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

string s, t;

int main() {
    cin >> s >> t;
    int ans = 0;
    while ((int)s.find(t) >= 0) {
        ans++;
        s = s.substr(s.find(t) + t.length());
    }
    cout << ans << endl;
    return 0;
}