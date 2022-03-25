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

int g[6] = { 4, 8, 15, 16, 23, 42 };

PII query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int x; cin >> x;
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (g[i] * g[j] == x) {
                // cout << g[i] << ' ' << g[j] << endl;
                return { g[i], g[j] };
            }
        }
    }
}

int main() {
    vector<int> ans;
    PII x1 = query(1, 2);
    PII x2 = query(2, 3);
    if (x1.first == x2.first || x1.first == x2.second) {
        ans.push_back(x1.second);
        ans.push_back(x1.first);
        if (x1.first == x2.first) ans.push_back(x2.second);
        else ans.push_back(x2.first);
    } else {
        ans.push_back(x1.first);
        ans.push_back(x1.second);
        if (x1.second == x2.first) ans.push_back(x2.second);
        else ans.push_back(x2.first);
    }
    PII x3 = query(3, 4);
    if (x3.first == ans.back()) ans.push_back(x3.second);
    else ans.push_back(x3.first);
    PII x4 = query(4, 5);
    if (x4.first == ans.back()) ans.push_back(x4.second);
    else ans.push_back(x4.first);
    for (int i = 0; i < 6; i++) {
        int f = 0;
        for (int j = 0; j < 5; j++) if (ans[j] == g[i]) f = 1;
        if (f == 0) {
            ans.push_back(g[i]);
        }
    }
    cout << "!";
    for (int& x: ans) cout << " " << x;
    cout << endl;
    return 0;
}