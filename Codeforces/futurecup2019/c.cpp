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

int n, ans;

int query(int l1, int r1, int l2, int r2) {
    cout << r1 - l1 + 1 << ' ' << r2 - l2 + 1;
    for (int i = l1; i <= r1; i++) cout << ' ' << i;
    for (int i = l2; i <= r2; i++) cout << ' ' << i;
    cout << endl; int ans; cin >> ans;
    return ans;
}
int query(vector<int>& v1, vector<int>& v2) {
    if (v1.empty() || v2.empty()) return 0;
    cout << (int)v1.size() << ' ' << (int)v2.size();
    for (int& x: v1) cout << ' ' << x;
    for (int& x: v2) cout << ' ' << x;
    cout << endl; int ans; cin >> ans;
    return ans;
}

vector<int> v1[20], v2[20];

void get(int l, int r, int d) {
    if (l >= r) return ;
    int m = (l + r) / 2;
    // ans = max(ans, query(l, m, m + 1, r));
    for (int i = l; i <= m; i++) {
        v1[d].push_back(i);
    }
    for (int i = m + 1; i <= r; i++) {
        v2[d].push_back(i);
    }
    get(l, m, d + 1); get(m + 1, r, d + 1); 
}

int main() {
    int T; cin >> T;
    while (T--) {
        for (int i = 0; i <= 9; i++) v1[i].clear(), v2[i].clear();
        cin >> n;
        ans = 0;
        get(1, n, 0);
        for (int i = 0; i < 9; i++) ans = max(ans, query(v1[i], v2[i]));
        cout << "-1 " << ans << endl;
    }    
    return 0;
}