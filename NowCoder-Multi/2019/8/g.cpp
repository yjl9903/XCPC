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

char s[maxn];

int main() {
    scanf("%s", s + 1);
    vector<PII> stk;
    int ans = 0;
    for (int i = 1; s[i]; i++) {
        int c = s[i] - 'A';
        stk.push_back({c, 1});
        while ((int)stk.size() >= 2 && stk[(int)stk.size() - 1].first == stk[(int)stk.size() - 2].first) {
            PII x = stk.back(); stk.pop_back();
            PII y = stk.back(); stk.pop_back();
            stk.push_back({ x.first, x.second + y.second });
        }
        // cout << i << " : \n";
        // for (auto x: stk) {
        //     cout << x.first << ' ' << x.second << endl;
        // }
        while (!stk.empty() && stk.back().second >= 3) {
            PII x = stk.back(); stk.pop_back();
            ans += x.second / 3;
            x.second -= x.second / 3 * 3;
            if (x.second) {
                stk.push_back(x);
            }
        }
    }
    cout << ans;
    return 0;
}