#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <string>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n;
char s[maxn];
vector<int> bag[3];

string get(int st) {
    string ans;
    int last = n + 1;
    for (int i = st; i < last; i++) {
        int ch = s[i] - 'a';
        // int pos = *lower_bound(bag[ch].begin(), bag[ch].end(), last) - 1;
        auto it = lower_bound(bag[ch].begin(), bag[ch].end(), last);
        if (it == bag[ch].begin()) continue;
        it--;
        int pos = *it;
        if (pos == i) {
            if (2 * (int)ans.length() + 1 >= n / 2) {
                ans += s[i];
                dbg(ans);
                for (int i = (int)ans.length() - 2; i >= 0; i--) ans += ans[i];
                return ans;
            }
            continue;
        } else if (pos < i) break;
        dbg(i, pos, s[i], s[pos]);
        ans += s[i]; last = pos;
    }
    for (int i = (int)ans.length() - 1; i >= 0; i--) ans += ans[i];
    return ans;
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) bag[s[i] - 'a'].push_back(i);
    // for (int i = 1; i <= n; i++) {
    //     string ans = get(i);
    //     if ((int)ans.length() >= n / 2) return printf("%s", ans.c_str()), 0;
    // }
    
    puts("IMPOSSIBLE");
    return 0;
}