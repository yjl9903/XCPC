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

int x;

int main() {
    cin >> x;
    vector<int> v; int c = 0;
    for (int i = 19; i >= 0; i--) {
        if (((x >> i) & 1) == 0) {
            // printf("%d ", i);
            v.push_back(i + 1);
            x ^= (1 << (i + 1)) - 1;
            int ans = 2 * (int)v.size() - 1;
            x++;
            for (int i = 0; i <= 22; i++) {
                if (x == (1 << i)) {
                    cout << ans << endl;
                    for (int& x: v) cout << x << ' ';
                    return 0;
                }
            }
        }
    }
    int ans = 2 * (int)v.size();
    for (int i = 0; i <= 22; i++) if (x == (1 << i)) ans--;
    cout << ans << endl;
    for (int& x: v) cout << x << ' ';
    return 0;
}