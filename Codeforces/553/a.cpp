#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n; char s[maxn];

int main() {
    cin >> n >> s;
    int ans = 1e9;
    for (int i = 0; i + 3 < n ; i++) {
        int x1 = min(min(abs(s[i] - 'A'), abs(26 + 'A' - s[i])), abs(26 + s[i] - 'A'));
        int x2 = min(min(abs(s[i + 1] - 'C'), abs(26 + 'C' - s[i + 1])), abs(26 + s[i + 1] - 'C'));
        int y1 = min(min(abs(s[i + 2] - 'T'), abs(26 + 'T' - s[i + 2])), abs(26 + s[i + 2] - 'T'));
        int y2 = min(min(abs(s[i + 3] - 'G'), abs(26 + 'G' - s[i + 3])), abs(26 + s[i + 3] - 'G'));
        dbg(x1, x2, y1, y2, abs('A' + 26 - s[i]));
        ans = min(ans, x1 + x2 + y1 + y2);
    }
    cout << ans;
    return 0;
}