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

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int ss = 1 << n, ans = 0;
        for (int s = 1; s < ss; s++) {
            vector<int> v;
            for (int i = 0; i < n; i++) if (s >> i & 1) v.push_back(a[i]);
            int f = 1;
            for (int i = 0; i < (int)v.size(); i++) {
                for (int j = i + 1; j < (int)v.size(); j++) {
                    if (gcd(v[i], v[j]) != 1) {
                        f = 0; break;
                    }
                }
                if (!f) break;
            }
            if (f) ans = max(ans, (int)v.size());
        }
        cout << ans << '\n';    
    }
    return 0;
}